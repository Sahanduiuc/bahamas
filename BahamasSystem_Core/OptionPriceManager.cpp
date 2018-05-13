#include "stdafx.h"
#include "OptionPriceManager.h"

OptionPriceManager::OptionPriceManager(std::queue<TradingEvent*>& eventsQueue,
	std::string ticker,
	boost::gregorian::date& startDate,
	boost::gregorian::date& endDate) :
	eventsQueue(eventsQueue) {

	this->currentPeriod = startDate - boost::gregorian::days(1);
	this->endPeriod = endDate;
	this->currentPeriodIndex = -1;

	ImportInstrumentData(ticker);

	std::cout << "All Option contracts for symbol " << ticker << " successfully loaded." << std::endl;
}

void OptionPriceManager::StreamNextEvent() {
	GetNextTradingTimeStamp();
	OptionChainUpdateEvent* updateEvent = new OptionChainUpdateEvent("CL");
	for(int i = 0; i < optionChainData.size(); i++){
		auto chainExpDate = 
			boost::gregorian::from_us_string(optionChainData[i]->ExpirationDate);
		currentPeriod = boost::gregorian::from_us_string(TradingTimeStamps[currentPeriodIndex]);

		if (chainExpDate > currentPeriod) {
			auto dte = chainExpDate - currentPeriod;
			optionChainData[i]->Dte = dte.days();
			updateEvent->OptionChains.push_back(optionChainData[i]);
		}
	}
	eventsQueue.push(updateEvent);
}

bool OptionPriceManager::EOD() {
	if (currentPeriodIndex == TradingTimeStamps.size()-1)
		return true;

	return false;
}

double OptionPriceManager::GetCurrentPrice(std::string contractID) {
	return OptionContracts[contractID]->MarketData().Ask;
}

BidAskDataFrame OptionPriceManager::GetCurrentDataFrame(std::string contractID) {
	return OptionContracts[contractID]->MarketData();
}

void OptionPriceManager::GetNextTradingTimeStamp() {
	currentPeriodIndex++;
}

std::string OptionPriceManager::GetCurrentTimeStampString() {
	return TradingTimeStamps[currentPeriodIndex];
}

void OptionPriceManager::ImportInstrumentData(std::string ticker) {
	CsvImporter importer;
	importer.SetDataPath("C:\\Users\\shami\\Desktop\\bahamas_data\\CL\\");
	std::vector<std::string> dataRow;

	//Load Trading timestamps
	importer.SetDataFile("exp_CL_dates.txt", 1);
	importer.GetDataItem(dataRow);
	while (!dataRow.empty())
	{
		dataRow.clear();
		importer.GetDataItem(dataRow);

		if (!dataRow.empty()) {
			TradingTimeStamps.push_back(dataRow[0]);
		}
	}

	//Load Chain data
	importer.SetDataFile("exp_CL_chains.csv", 3);
	dataRow.clear();
	importer.GetDataItem(dataRow);
	while(!dataRow.empty()){
		dataRow.clear();
		importer.GetDataItem(dataRow);

		if (!dataRow.empty()) {
			OptionChain* tempChain = new OptionChain;
			tempChain->ChainId = dataRow[0];
			tempChain->UnderlyingTicker = "CL";
			tempChain->OptionTicker = dataRow[1];
			tempChain->ExpirationDate = dataRow[2];
			tempChain->Multiplier = 1000;
			tempChain->Dte = 0;

			optionChainData.push_back(tempChain);
			OptionChains[tempChain->ChainId] = tempChain;
		}
	}

	//Load Contract data
	importer.SetDataFile("exp_CL_contracts.csv", 5);
	importer.GetDataItem(dataRow);
	while (!dataRow.empty()) {
		dataRow.clear();
		importer.GetDataItem(dataRow);

		if (!dataRow.empty()) {
			double strike_d = stod(dataRow[2]);
			std::string& chainId = dataRow[1];
			OptionContract* optionContract = new OptionContract(dataRow[0], 
				"CL",
				OptionChains[chainId]->OptionTicker, 
				OptionChains[chainId]->ExpirationDate,
				strike_d, 
				dataRow[3][0], 
				*this);

			OptionContracts[dataRow[0]] = optionContract;
			closeMappings[stoi(dataRow[4])] = optionContract;
			OptionChains[chainId]->OptionContracts.push_back(optionContract);
			OptionChains[chainId]->ContractMappings[dataRow[0]] = optionContract;

			if (dataRow[3][0] == 'C') {
				OptionChains[chainId]->CallStrikes.push_back(strike_d);
				OptionChains[chainId]->CallStrikeMappings[strike_d] = optionContract;

				if (strike_d > OptionChains[chainId]->MaxCallStrike)
					OptionChains[chainId]->MaxCallStrike = strike_d;
				if (strike_d < OptionChains[chainId]->MinCallStrike)
					OptionChains[chainId]->MinCallStrike = strike_d;
			}
			else if (dataRow[3][0] == 'P') {
				OptionChains[chainId]->PutStrikes.push_back(strike_d);
				OptionChains[chainId]->PutStrikeMappings[strike_d] = optionContract;

				if (strike_d > OptionChains[chainId]->MaxPutStrike)
					OptionChains[chainId]->MaxPutStrike = strike_d;
				if (strike_d < OptionChains[chainId]->MinPutStrike)
					OptionChains[chainId]->MinPutStrike = strike_d;
			}
		}
	}

	std::cout << "Loading Price Data...." << std::endl;

	boost::iostreams::mapped_file mmap("C:\\Users\\shami\\Desktop\\bahamas_data\\CL\\exp_CL_data.csv",
		boost::iostreams::mapped_file::readonly);
	LoadPriceData(mmap,2762,mmap.size());
}

void OptionPriceManager::LoadPriceData(boost::iostreams::mapped_file& mmap,
	size_t offsetBegin,size_t offsetEnd) {
	const char* f = mmap.const_data() + offsetBegin;
	auto l = mmap.const_data() + offsetEnd;
	std::vector<char*> data;
	uint16_t col_index = 0;
	size_t max_col = TradingTimeStamps.size() + 1;
	uint32_t row_index = 0;

	while (f && f != l) {
		while (*f != '\n' && f && f != l) {
			int c = 0;
			char str[] = "               ";
			while (*f != ',' && *f != '\n' && *f != '\r') {
				str[c] = f[0];
				c++;
				f++;
			}
			f++;

			double val = atof(str);

			if (col_index == 0) {
				row_index = val;
			}
			else if (col_index > 0 && val != -1.0) {
				BidAskDataFrame dataFrame{
					closeMappings[row_index]->Id,
					TradingTimeStamps[col_index - 1],
					val * 1000.0,
					0,
					val * 1000.0,
					0,
					100 //TODO Delta
				};
				closeMappings[row_index]->AddMarketData(
					TradingTimeStamps[col_index - 1],
					dataFrame);
			}

			col_index++;
			if (col_index >= max_col)
				col_index = 0;
		}
		f++;
	}
}
