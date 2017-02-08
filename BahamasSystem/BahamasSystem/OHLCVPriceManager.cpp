/*
 * OHLCVDataParser.cpp
 *
 *  Created on: 23 Oct 2016
 *      Author: shamitha
 */

#include "OHLCVPriceManager.h"

OHLCVPriceManager::OHLCVPriceManager(std::queue<TradingEvent*>& eventsQueue, std::vector<std::string> tickers,
	boost::gregorian::date& startDate, boost::gregorian::date& endDate):
									eventsQueue(eventsQueue) {

	this->currentPeriod = startDate;
	this->endPeriod = endDate;

	for (auto ticker : tickers)
		ImportInstrumentData(ticker);
}

OHLCVPriceManager::~OHLCVPriceManager() {

}

bool OHLCVPriceManager::EOD() {
	if (currentPeriod >= endPeriod)
		return true;

	return false;
}

void OHLCVPriceManager::StreamNextEvent(){
	if (InstrumentData.find(currentPeriod) != InstrumentData.end()) {
		for (OHCLVDataFrame& dataFrame : InstrumentData[currentPeriod]) {
			TradingEvent* tempDataFrame = new BarEvent(dataFrame.Ticker,
				dataFrame.Open,
				dataFrame.High,
				dataFrame.Low,
				dataFrame.Settle);
			eventsQueue.push(tempDataFrame);
		}
		readCount++;
	}

	currentPeriod += boost::gregorian::days(1);
}

double OHLCVPriceManager::GetCurrentPrice(std::string ticker) {

	//std::string dateTest = ConvData(currentPeriod - boost::gregorian::days(1));

	boost::gregorian::date targetDate = currentPeriod - boost::gregorian::days(1);
	
	for (OHCLVDataFrame& frame : InstrumentData[targetDate]) {
		if (ticker == frame.Ticker)
			return frame.Settle;
	}

	//TODO: Throw exception, ticker not found in price data
	return -1;
}

void OHLCVPriceManager::ImportInstrumentData(std::string ticker){

	CSVImporter csvImporter;
	csvImporter.SetLoadTicker(ticker);

	std::vector<std::string> dataRow;

	//Skip header row
	csvImporter.GetDataItem(dataRow);

	csvImporter.GetDataItem(dataRow);
	while(!dataRow.empty()){
		boost::gregorian::date eventDate =
				boost::gregorian::from_string(dataRow[0]);

		InstrumentData[eventDate].push_back(OHCLVDataFrame{
			ticker,
			eventDate,
			atof(dataRow[1].c_str()),
			atof(dataRow[2].c_str()),
			atof(dataRow[3].c_str()),
			atof(dataRow[4].c_str())
		});

		csvImporter.GetDataItem(dataRow);
	}
}

std::string OHLCVPriceManager::GetDataFrameTimeStamp() {
	return ConvData(currentPeriod - boost::gregorian::days(1));
}
