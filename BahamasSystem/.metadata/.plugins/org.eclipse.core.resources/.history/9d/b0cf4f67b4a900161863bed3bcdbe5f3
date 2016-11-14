/*
 * OHLCVDataParser.h
 *
 *  Created on: 23 Oct 2016
 *      Author: shamitha
 */

#ifndef OHLCVPRICEMANAGER_H_
#define OHLCVPRICEMANAGER_H_

#include <queue>
#include <boost/bind.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"

#include "DataImporter.h"
#include "PriceManager.h"
#include "TradingEvent.h"

struct OHCLVDataFrame{
	boost::gregorian::date EventDateTime;
	double AdjPrice;
};

class OHLCVPriceManager: public PriceManager{
public:
	std::map<boost::gregorian::date,std::vector<OHCLVDataFrame> > InstrumentData;

	OHLCVPriceManager(std::queue<TradingEvent>&, std::string);
	~OHLCVPriceManager();
private:
	std::queue<TradingEvent>& eventsQueue;
	boost::gregorian::date currentPeriod;

	void ImportInstrumentData(std::string);
};

#endif /* DATAHANDLERS_OHLCVPRICEMANAGER_H_ */
