#include "stdafx.h"
#include "OptionPriceManager.h"

OptionPriceManager::OptionPriceManager(std::queue<TradingEvent*>& eventsQueue,
	std::string ticker,
	boost::gregorian::date& startDate,
	boost::gregorian::date& endDate) :
	eventsQueue(eventsQueue) {

	this->currentPeriod = startDate;
	this->endPeriod = endDate;

	ImportInstrumentData(ticker);

	std::cout << "All Option contracts for symbol " << ticker << " successfully loaded." << std::endl;
}

void OptionPriceManager::StreamNextEvent() {

}

double OptionPriceManager::GetCurrentPrice(std::string contractID) {
	return 0;
}

void OptionPriceManager::ImportInstrumentData(std::string ticker) {
	CsvImporter dataImporter;
	std::string fPath = "..\\data\\Options\\ES\\";
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
	io::CSVReader<16> in(file);
	in.read_header(io::ignore_missing_column, "date", "underlying", "root_symbol",
		"exchange", "futures_symbol", "futures_expiration_date",
		"futures_close", "options_expiration_date", "strike",
		"type", "style", "bid", "ask", "settlement", "volume", "open_interest");
	std::string date, underlying, rootSymbol, exchange,
		futuresSymbol, futuresExpDate, futuresClose, optionExpDate,
		strike, type, style, bid, ask, settlement, volume, openIntrest;

	while (in.read_row(date, underlying, rootSymbol, exchange,
		futuresSymbol, futuresExpDate, futuresClose, optionExpDate,
		strike, type, style, bid, ask, settlement, volume, openIntrest)) {

		std::string chainId = rootSymbol + "_" + optionExpDate;
		std::string contractId = chainId + "_" + type + "_" + strike;
		OptionContract tempContract{
			contractId,
			underlying,
			rootSymbol,
			optionExpDate
		};

		BidAskDataFrame dataFrame{
			rootSymbol,
			date,
			stod(bid),
			0,
			stod(ask),
			0
		};
		bool chainExists = false;
		for (auto& chain : OptionChainData) {
			if (chain.ChainId == chainId) {
				if (chain.OptionContracts.find(contractId) == chain.OptionContracts.end()) {
					chain.OptionContracts[contractId] = tempContract;
				}
				chain.OptionContracts[contractId].PriceData[date] = dataFrame;
				chainExists = true;
				break;
			}
		}
		if (!chainExists) {
			OptionChain tempChain(chainId,underlying, rootSymbol, optionExpDate);
			OptionChainData.push_back(tempChain);
		}
	}

}

