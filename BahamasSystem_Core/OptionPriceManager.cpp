#include "stdafx.h"
#include "OptionPriceManager.h"

OptionPriceManager::OptionPriceManager(std::queue<TradingEvent*>& eventsQueue,
	std::string ticker,
	boost::gregorian::date& startDate,
	boost::gregorian::date& endDate) :
	eventsQueue(eventsQueue) {

	this->currentPeriod = startDate - boost::gregorian::days(1);
	this->endPeriod = endDate;

	ImportInstrumentData(ticker);

	std::cout << "All Option contracts for symbol " << ticker << " successfully loaded." << std::endl;
}

void OptionPriceManager::StreamNextEvent() {
	GetNextTradingTimeStamp();
	OptionChainUpdateEvent* updateEvent = new OptionChainUpdateEvent("CL");
	for(int i = 0; i < optionChainData.size(); i++){
		auto chainExpDate = 
			boost::gregorian::from_us_string(optionChainData[i].ExpirationDate);
		
		if (chainExpDate > currentPeriod) {
			updateEvent->OptionChains.push_back(&optionChainData[i]);
			auto dte = chainExpDate - currentPeriod;
			optionChainData[i].Dte = dte.days();
		}
	}
	eventsQueue.push(updateEvent);
}

bool OptionPriceManager::EOD() {
	if (currentPeriod > endPeriod || eod)
		return true;

	return false;
}


double OptionPriceManager::GetCurrentPrice(std::string contractID) {
	return optionContracts[contractID]->MarketData().Ask;
}

void OptionPriceManager::ImportInstrumentData(std::string ticker) {
	CsvImporter dataImporter;
	std::string fPath = "..\\data\\Options\\CL\\";
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
}

void OptionPriceManager::ImportOptionData(std::string file) {
	io::CSVReader<17> in(file);
	in.read_header(io::ignore_missing_column, "date", "underlying", "root_symbol",
		"exchange", "futures_symbol", "futures_expiration_date",
		"futures_close", "options_expiration_date", "strike",
		"type", "style", "bid", "ask", "settlement", "volume", "open_interest", "dte");
	std::string date, underlying, rootSymbol, exchange,
		futuresSymbol, futuresExpDate, futuresClose, optionExpDate,
		strike, style, bid, ask, settlement, volume, openIntrest, dte;
	char type;
	while (in.read_row(date, underlying, rootSymbol, exchange,
		futuresSymbol, futuresExpDate, futuresClose, optionExpDate,
		strike, type, style, bid, ask, settlement, volume, openIntrest, dte)) {

		int dte_i = stoi(dte);
		if (dte_i == 0 || dte_i > 200)
			continue;

		std::string chainId = rootSymbol + "_" + optionExpDate;
		std::string contractId = chainId + "_" + type + "_" + strike;

		BidAskDataFrame dataFrame{
			rootSymbol,
			date,
			stod(settlement) * 1000.0,
			0,
			stod(settlement) * 1000.0,
			0
		};

		double strike_d = stod(strike);
		auto optionContract = new OptionContract(contractId, underlying, 
			rootSymbol, optionExpDate, strike_d, type,*this);

		bool chainExists = false;
		for (auto& chain : optionChainData) {
			if (chain.ChainId == chainId) {
				if (chain.ContractMappings.find(contractId) == chain.ContractMappings.end()) {
					chain.ContractMappings[contractId] = optionContract;
					chain.OptionContracts.push_back(chain.ContractMappings[contractId]);

					if (type == 'C') {
						chain.CallStrikes.push_back(strike_d);
						chain.CallStrikeMappings[strike_d] = optionContract;

						if (strike_d > chain.MaxCallStrike)
							chain.MaxCallStrike = strike_d;
						if (strike_d < chain.MinCallStrike)
							chain.MinCallStrike = strike_d;
					}
					else if (type == 'P') {
						chain.PutStrikes.push_back(strike_d);
						chain.PutStrikeMappings[strike_d] = optionContract;

						if (strike_d > chain.MaxPutStrike)
							chain.MaxPutStrike = strike_d;
						if (strike_d < chain.MinPutStrike)
							chain.MinPutStrike = strike_d;
					}
				}
				chain.ContractMappings[contractId]->AddMarketData(date, dataFrame);
				chainExists = true;

				optionContracts[contractId] = chain.ContractMappings[contractId];
				break;
			}
		}
		if (!chainExists) {
			OptionChain tempChain = {
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
	}
	//boost::iostreams::mapped_file mmap(file, boost::iostreams::mapped_file::readonly);
	//const char* f = mmap.const_data();
	//auto l = f + mmap.size();

	//uintmax_t m_numLines = 0;
	//
	//while (f && f != l) {
	//	std::vector<char*> data;
	//	while (*f != '\n' && f && f != l) {
	//		int c = 0;
	//		char str[] = "00000000000000000000000000000";
	//		while (*f != ',' && *f != '\n' && *f != '\r') {
	//			str[c] = f[0];
	//			c++;
	//			f++;
	//		}
	//		f++;
	//	}
	//	m_numLines++;
	//	f++;
	//}
}

void OptionPriceManager::GetNextTradingTimeStamp() {
	currentPeriod += boost::gregorian::days(1);
}

std::string OptionPriceManager::GetCurrentTimeStampString() {
	std::ostringstream os;
	auto* facet(new boost::gregorian::date_facet("%m/%d/%Y"));
	os.imbue(std::locale(os.getloc(), facet));
	os << currentPeriod;
	return os.str();
}