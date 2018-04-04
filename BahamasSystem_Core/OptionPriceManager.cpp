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
			std::string fName = i->path().filename().string();
			std::cout << "Importing file " << fName << std::endl;

			ImportOptionData(fPath, fName);
		}
		else
			continue;
	}
}

void OptionPriceManager::ImportOptionData(std::string fPath, std::string fName) {
	io::CSVReader<16> in(fPath + fName);
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

		std::string contractId = underlying + "_" + rootSymbol + "_" + strike + "_" + type + "_" + optionExpDate;
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

		if (OptionPriceData.find(tempContract) == OptionPriceData.end()) {
			std::map<std::string, BidAskDataFrame> timeSeries{ { date, dataFrame } };
			OptionPriceData[tempContract] = timeSeries;
		}
		else {
			OptionPriceData[tempContract][date] = dataFrame;
		}
	}
}

