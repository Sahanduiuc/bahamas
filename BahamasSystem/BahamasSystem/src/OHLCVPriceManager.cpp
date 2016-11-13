/*
 * OHLCVDataParser.cpp
 *
 *  Created on: 23 Oct 2016
 *      Author: shamitha
 */

#include "OHLCVPriceManager.h"

OHLCVPriceManager::OHLCVPriceManager(std::queue<TradingEvent>& eventsQueue, std::string ticker):
									eventsQueue(eventsQueue) {
	ImportInstrumentData(ticker);
}


OHLCVPriceManager::~OHLCVPriceManager() {

}

void OHLCVPriceManager::ImportInstrumentData(std::string ticker){

	CSVImporter csvImporter;
	std::vector<std::string> dataRow;

	//Skip header row
	csvImporter.GetDataItem(dataRow);

	csvImporter.GetDataItem(dataRow);
	while(!dataRow.empty()){
		boost::gregorian::date eventDate = boost::gregorian::from_string(dataRow[0]);

		if(InstrumentData.empty()){
			currentPeriod = eventDate;
		}

		InstrumentData[eventDate].push_back(OHCLVDataFrame{
			eventDate,
			atof(dataRow[6].c_str())
		});

		csvImporter.GetDataItem(dataRow);
	}
}

