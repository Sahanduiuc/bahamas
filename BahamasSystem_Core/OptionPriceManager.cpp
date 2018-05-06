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
	//ExperimentalDataLoad(ticker);

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
			updateEvent->OptionChains.push_back(optionChainData[i]);
			auto dte = chainExpDate - currentPeriod;
			optionChainData[i]->Dte = dte.days();
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

void OptionPriceManager::ImportInstrumentData(std::string ticker) {
	CsvImporter dataImporter;
	std::string fPath = "C:\\Users\\shami\\Desktop\\bahamas_data\\CL\\";
	dataImporter.SetDataPath(fPath);

	//Import all available option chains TODO use given dates
	boost::filesystem::path p(fPath);

	for (auto i = boost::filesystem::directory_iterator(p);
		i != boost::filesystem::directory_iterator(); i++)
	{
		if (!is_directory(i->path()))
		{
			std::string file = i->path().filename().string();
			std::cout << "Importing file " << file << std::endl;
			ImportOptionData(fPath + file);
		}
		else
			continue;
	}

	//TEMP Override timestamp stream
	io::CSVReader<1> in(fPath + "meta\\trading_timestamps.csv");
	in.read_header(io::ignore_missing_column, "date");
	std::string date;
	while (in.read_row(date)) {
		TradingTimeStamps.push_back(date);
	}

}

void OptionPriceManager::ImportOptionData(std::string file) {
	io::CSVReader<18> in(file);
	in.read_header(io::ignore_missing_column, "date", "underlying", "root_symbol",
		"futures_symbol", "exchange", "futures_expiration_date",
		"futures_close", "options_expiration_date", "strike",
		"type", "style", "bid", "ask", "settlement", "volume", "open_interest", "dte","delta");
	std::string date, underlying, rootSymbol, futuresSymbol,
		exchange, futuresExpDate, futuresClose, optionExpDate,
		strike, style, bid, ask, settlement, volume, openIntrest, dte, delta;
	char type;
	while (in.read_row(date, underlying, rootSymbol, futuresSymbol,
		exchange, futuresExpDate, futuresClose, optionExpDate,
		strike, type, style, bid, ask, settlement, volume, openIntrest, dte, delta)) {

		int dte_i = stoi(dte);
		if (dte_i == 0 || dte_i > 200)
			continue;
		if (rootSymbol != "CL")
			continue;

		std::string chainId = rootSymbol + "_" + optionExpDate;
		std::string contractId = chainId + "_" + type + "_" + strike;

		BidAskDataFrame dataFrame{
			rootSymbol,
			date,
			stod(settlement) * 1000.0,
			0,
			stod(settlement) * 1000.0,
			0,
			stod(delta)
		};

		double strike_d = stod(strike);
		auto optionContract = new OptionContract(contractId, underlying, 
			rootSymbol, optionExpDate, strike_d, type,*this);

		bool chainExists = false;
		for (auto& chain : optionChainData) {
			if (chain->ChainId == chainId) {
				if (chain->ContractMappings.find(contractId) == chain->ContractMappings.end()) {
					chain->ContractMappings[contractId] = optionContract;
					chain->OptionContracts.push_back(chain->ContractMappings[contractId]);

					if (type == 'C') {
						chain->CallStrikes.push_back(strike_d);
						chain->CallStrikeMappings[strike_d] = optionContract;

						if (strike_d > chain->MaxCallStrike)
							chain->MaxCallStrike = strike_d;
						if (strike_d < chain->MinCallStrike)
							chain->MinCallStrike = strike_d;
					}
					else if (type == 'P') {
						chain->PutStrikes.push_back(strike_d);
						chain->PutStrikeMappings[strike_d] = optionContract;

						if (strike_d > chain->MaxPutStrike)
							chain->MaxPutStrike = strike_d;
						if (strike_d < chain->MinPutStrike)
							chain->MinPutStrike = strike_d;
					}
				}
				chain->ContractMappings[contractId]->AddMarketData(date, dataFrame);
				chainExists = true;

				OptionContracts[contractId] = chain->ContractMappings[contractId];
				break;
			}
		}
		if (!chainExists) {
			OptionChain* tempChain = new OptionChain{
				chainId,
				underlying,
				rootSymbol,
				optionExpDate,
				1000,
				dte_i
			};

			optionChainData.push_back(tempChain);
		}

		underlyingPrices[date] = stod(futuresClose);
		FuturesContractDataFrame futDataFrame = {
			underlying,
			date,
			futuresSymbol,
			stod(futuresClose)
		};
		underlyingData[date].push_back(futDataFrame);
	}
}

void OptionPriceManager::GetNextTradingTimeStamp() {
	//currentPeriod += boost::gregorian::days(1);
	currentPeriodIndex++;
}

std::string OptionPriceManager::GetCurrentTimeStampString() {
	//std::ostringstream os;
	//auto* facet(new boost::gregorian::date_facet("%m/%d/%Y"));
	//os.imbue(std::locale(os.getloc(), facet));
	//os << currentPeriod;
	//return os.str();
	return TradingTimeStamps[currentPeriodIndex];
}

void OptionPriceManager::ExperimentalDataLoad(std::string ticker) {
	io::CSVReader<1> in("..\\data\\Options\\CL\\experimental\\exp_CL_dates.csv");
	in.read_header(io::ignore_missing_column, "date");
	std::string date;
	while (in.read_row(date)) {
		TradingTimeStamps.push_back(date);
	}
	
	LoadChainData();
	LoadContractData();
	LoadPriceData();
}

void OptionPriceManager::LoadChainData() {
	io::CSVReader<3> in("..\\data\\Options\\CL\\experimental\\exp_CL_chains.csv");
	in.read_header(io::ignore_missing_column, "id","option_symbol","expiration_date");
	std::string id, option_symbol, expiration_date;
	while (in.read_row(id, option_symbol, expiration_date)) {
		OptionChain* tempChain = new OptionChain;
		tempChain->ChainId = id;
		tempChain->UnderlyingTicker = "CL";
		tempChain->OptionTicker = option_symbol;
		tempChain->ExpirationDate = expiration_date;
		tempChain->Multiplier = 1000;
		tempChain->Dte = 1000; //TODO update DTE

		optionChainData.push_back(tempChain);
		OptionChains[id] = tempChain;
	}
}

void OptionPriceManager::LoadContractData() {
	io::CSVReader<7> in("..\\data\\Options\\CL\\experimental\\exp_CL_contracts.csv");
	in.read_header(io::ignore_missing_column, "id", "option_symbol", "expiration_date",
		"strike", "type", "chain_id", "close_index");
	std::string id, option_symbol, expiration_date, strike, chain_id, close_index;
	char type;
	while (in.read_row(id, option_symbol, expiration_date, strike,
		type, chain_id, close_index)) {

		double strike_d = stod(strike);
		OptionContract* optionContract = new OptionContract(id, "CL", 
			option_symbol, expiration_date, strike_d, type,*this);

		OptionContracts[id] = optionContract;
		closeMappings[stoi(close_index)] = optionContract;
		OptionChains[chain_id]->OptionContracts.push_back(optionContract);
		OptionChains[chain_id]->ContractMappings[id] = optionContract;

		if (type == 'C') {
			OptionChains[chain_id]->CallStrikes.push_back(strike_d);
			OptionChains[chain_id]->CallStrikeMappings[strike_d] = optionContract;

			if (strike_d > OptionChains[chain_id]->MaxCallStrike)
				OptionChains[chain_id]->MaxCallStrike = strike_d;
			if (strike_d < OptionChains[chain_id]->MinCallStrike)
				OptionChains[chain_id]->MinCallStrike = strike_d;
		}
		else if (type == 'P') {
			OptionChains[chain_id]->PutStrikes.push_back(strike_d);
			OptionChains[chain_id]->PutStrikeMappings[strike_d] = optionContract;

			if (strike_d > OptionChains[chain_id]->MaxPutStrike)
				OptionChains[chain_id]->MaxPutStrike = strike_d;
			if (strike_d < OptionChains[chain_id]->MinPutStrike)
				OptionChains[chain_id]->MinPutStrike = strike_d;
		}
	}
}

void OptionPriceManager::LoadPriceData() {
	boost::iostreams::mapped_file mmap("..\\data\\Options\\CL\\experimental\\exp_CL_data.csv",
		boost::iostreams::mapped_file::readonly);
	const char* f = mmap.const_data();
	auto l = f + mmap.size();
	std::vector<char*> data;
	uint16_t col_index = 0;
	size_t max_col = TradingTimeStamps.size() + 1;
	uint32_t row_index = 0;

	//Skip header
	while (*f != '\n' && f && f != l) {
		f++;
	}

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
			else if(col_index > 0 && val != -1.0) {
				BidAskDataFrame dataFrame{
					closeMappings[row_index]->Id,
					TradingTimeStamps[col_index - 1],
					val * 1000.0,
					0,
					val * 1000.0,
					0,
					100 //TODO Delta
				};
				closeMappings[row_index]->AddMarketData(TradingTimeStamps[col_index - 1],
					dataFrame);
			}

			col_index++;
			if (col_index >= max_col)
				col_index = 0;
		}
		f++;
	}
}