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
	dataImporter.SetDataPath("..\\data\\RUT\\");

	//Import all available option chains TODO use given dates
	boost::filesystem::path p("..\\data\\RUT\\");
	for (auto i = boost::filesystem::directory_iterator(p); 
		i != boost::filesystem::directory_iterator(); i++)
	{
		if (!is_directory(i->path())) //we eliminate directories
		{
			std::string fName = i->path().filename().string();
			dataImporter.SetLoadFile(fName);

			std::vector<std::string> dataRow;
			//Skip header row
			dataImporter.GetDataItem(dataRow);

			dataImporter.GetDataItem(dataRow);
			while (!dataRow.empty()) {
				boost::gregorian::date eventDate =
					boost::gregorian::from_string(dataRow[0]);

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


