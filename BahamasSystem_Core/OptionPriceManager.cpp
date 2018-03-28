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

void OptionPriceManager::ImportInstrumentData(std::string ticker) {
	CsvImporter dataImporter;
	std::string fPath = "..\\data\\RUT\\";
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

			io::CSVReader<9> in(fPath + fName);
			in.read_header(io::ignore_missing_column, "Date", "ExpDate", "Strike", "Type", "Mid", "Delta", "Gamma", "Vega", "Theta");
			std::string date, expDate, type, strike, mid, delta, gamma, vega, theta;

			while (in.read_row(date, expDate, strike, type, 
				mid, delta, gamma, vega, theta)) {
				std::string contractId = ticker + "_" + strike + "_" + type + "_" + expDate;
				OptionContract tempContract{
					contractId,
					ticker,
					expDate
				};

				BidAskDataFrame dataFrame{
					ticker,
					date,
					stod(mid),
					0,
					stod(mid),
					0
				};

				if (InstrumentData.find(tempContract) == InstrumentData.end()) {			
					std::map<std::string, BidAskDataFrame> timeSeries{ {date, dataFrame} };
					InstrumentData[tempContract] = timeSeries;
				}
				else {
					InstrumentData[tempContract][date] = dataFrame;
				}
			}
		}
		else
			continue;
	}
}

void OptionPriceManager::StreamNextEvent() {

}

double OptionPriceManager::GetCurrentPrice(std::string contractID) {
	return 0;
}


