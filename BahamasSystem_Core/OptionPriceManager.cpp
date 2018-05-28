#include "stdafx.h"
#include "OptionPriceManager.h"

OptionPriceManager::OptionPriceManager(std::queue<TradingEvent*>& eventsQueue,
	std::string ticker,
	boost::gregorian::date& startDate,
	boost::gregorian::date& endDate) :
	eventsQueue(eventsQueue) {

	this->currentPeriod = startDate - boost::gregorian::days(1);
	this->endPeriod = endDate;
	this->currentDateIndex = -1;
	this->QuoteTime = "19:00";

	Logger::instance().LogInfo("Loading contract metadata for symbol " + ticker +
		"....");

	this->TestMethod();
	this->ImportInstrumentData(ticker);

	Logger::instance().LogInfo("All Contract Metadata for symbol " + ticker +
		" successfully loaded.");
}

void OptionPriceManager::StreamNextEvent() {
	GetNextTradingTimeStamp();
	OptionChainUpdateEvent* updateEvent = new OptionChainUpdateEvent("CL");
	currentPeriod = boost::gregorian::date_from_iso_string(TradingDates[currentDateIndex]);
	for (auto& element : OptionChainHistory[TradingDates[currentDateIndex]]) {
		auto chainExpDate = boost::gregorian::date_from_iso_string(
			element.second->ExpirationDate);

		auto dte = chainExpDate - currentPeriod;
		OptionChainHistory[TradingDates[currentDateIndex]][element.first]->Dte = dte.days();
		updateEvent->OptionChains.push_back(element.second);
	}

	eventsQueue.push(updateEvent);
}

bool OptionPriceManager::EOD() {
	if (currentDateIndex == TradingDates.size()-1)
		return true;

	return false;
}

double OptionPriceManager::GetCurrentPrice(std::string contractID) {
	OptionDataFrame dataframe = this->GetCurrentDataFrame(contractID);	
	return (dataframe.Ask + dataframe.Bid)/2.0;
}

OptionDataFrame OptionPriceManager::GetCurrentDataFrame(std::string contractID) {
	CsvImporter importer;
	importer.SetDataPath("D:\\bahamas_data\\CL\\2017\\" +
		TradingDates[currentDateIndex] + "\\LO\\");
	std::vector<std::string> dataRow;

	importer.SetDataFile(contractID + ".csv", 57);
	importer.GetDataItem(dataRow);
	int count = 10;
	while (!dataRow.empty()) {
		dataRow.clear();
		importer.GetDataItem(dataRow);

		if (!dataRow.empty()) {
			if (count == 0) {
				double ask = 0.0;
				double bid = 0.0;
				if (dataRow[37] == "" && dataRow[40] == "")
				{
					Logger::instance().LogError("Error in dataset: No Bid/Ask");
				}
				else if (dataRow[37] == "") {
					bid = stod(dataRow[40]);
					ask = stod(dataRow[40]);
				}
				else if (dataRow[40] == "") {
					bid = stod(dataRow[37]);
					ask = stod(dataRow[37]);
				}
				else {
					bid = stod(dataRow[37]);
					ask = stod(dataRow[40]);
				}

				double mid = (bid + ask)/2.0;
				double underlying = 55.66;
				double dte = (OptionChainHistory[TradingDates[currentDateIndex]]
					[OptionContracts[contractID]->ChainId]->Dte)/365.0;
				double strike = OptionContracts[contractID]->Strike;

				double iv = OptionPricer::instance().ImpliedVolatility('P', 
					underlying, strike, 0.00691, dte, mid);
				double delta = OptionPricer::instance().PutDelta(underlying,
					OptionContracts[contractID]->Strike,
					0.00691, iv, dte) * 100;
				
				OptionDataFrame tempFrame{
					contractID,
					TradingDates[currentDateIndex],
					bid * 1000.0,
					0.0,
					ask * 1000.0,
					0.0,
					delta
				};
				return tempFrame;
			}
		}
		count--;
	}
	return *(new OptionDataFrame);
}

void OptionPriceManager::GetNextTradingTimeStamp() {
	currentDateIndex++;
}

std::string OptionPriceManager::GetCurrentTimeStampString() {
	return TradingDates[currentDateIndex];
}

void OptionPriceManager::ImportInstrumentData(std::string ticker) {
	CsvImporter importer;
	importer.SetDataPath("D:\\bahamas_data\\CL\\");
	std::vector<std::string> dataRow;

	//Load Futures Data
	importer.SetDataFile("FUT_Continuous.csv",12);
	importer.GetDataItem(dataRow);
	while (!dataRow.empty()) {
		dataRow.clear();
		importer.GetDataItem(dataRow);

		if (!dataRow.empty()) {
			TradingDates.push_back(dataRow[0]);
			FuturesContractDataFrame dataframe{
				"CL",
				dataRow[0],
				"CL1",
				dataRow[0],
				stod(dataRow[4])
			};
			FuturesData["CL1"][dataRow[0]] = dataframe;
		}
	}

	//Load Manifest data
	for (int i = 0; i < TradingDates.size(); i++) {
		importer.SetDataPath("D:\\bahamas_data\\CL\\Manifests\\");

		importer.SetDataFile(TradingDates[i] + ".csv", 5);
		dataRow.clear();
		importer.GetDataItem(dataRow);
		while (!dataRow.empty()) {
			dataRow.clear();
			importer.GetDataItem(dataRow);

			if (!dataRow.empty()) {
				double strike_d = stod(dataRow[4]) / 100.0;
				std::string& chainId = dataRow[1];
				std::string& expDate = dataRow[2];
				std::string& contractId = dataRow[0];
				char type = dataRow[3][0];

				OptionChain* tempChain = new OptionChain;
				tempChain->ChainId = chainId;
				tempChain->UnderlyingTicker = ticker;
				tempChain->OptionTicker = "LO";
				tempChain->ExpirationDate = expDate;
				tempChain->Multiplier = 1000;
				tempChain->Dte = 0;

				if (OptionChainHistory[TradingDates[i]].find(chainId) ==
					OptionChainHistory[TradingDates[i]].end()) {
					OptionChainHistory[TradingDates[i]][chainId] = tempChain;
				}
				OptionChain* targetChain = OptionChainHistory[TradingDates[i]][chainId];

				OptionContract* optionContract = new OptionContract(contractId,
					ticker, "LO", expDate, strike_d, type, chainId, *this);
				
				if (OptionContracts.find(contractId) == OptionContracts.end()) {
					OptionContracts[contractId] = optionContract;
				}

				targetChain->OptionContracts.push_back(optionContract);

				if (type == 'C') {
					targetChain->CallStrikes.push_back(strike_d);
					targetChain->CallStrikeMappings[strike_d] = optionContract;

					if (strike_d > targetChain->MaxCallStrike)
						targetChain->MaxCallStrike = strike_d;
					if (strike_d < targetChain->MinCallStrike)
						targetChain->MinCallStrike = strike_d;
				}
				else if (type == 'P') {
					targetChain->PutStrikes.push_back(strike_d);
					targetChain->PutStrikeMappings[strike_d] = optionContract;

					if (strike_d > targetChain->MaxPutStrike)
						targetChain->MaxPutStrike = strike_d;
					if (strike_d < targetChain->MinPutStrike)
						targetChain->MinPutStrike = strike_d;
				}


			}
		}
	}
}

void OptionPriceManager::TestMethod() {
	auto chainExpDate = boost::gregorian::date_from_iso_string("20170215");
	auto d = chainExpDate.year_month_day();

	double underlying = 56.58;  // Underlying price
	double strike = 56;  // Strike price
	double r = 0.02;   // Risk-free rate (5%)
	double v = 0.2;    // Volatility of the underlying (20%)
	double T = 72.0/365.0;    // One year until expiry

	//double call = OptionPricer::instance().CallPrice(underlying, strike, r, v, T);
	//double delta = OptionPricer::instance().CallDelta(underlying, strike, r, v, T);

	double volest = OptionPricer::instance().ImpliedVolatility('P', underlying, strike, r, T, 2.72);
}