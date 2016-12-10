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
	std::string Ticker;
	boost::gregorian::date EventDateTime;
	double Open;
	double AdjPrice;
};

class OHLCVPriceManager: public PriceManager{
public:

	OHLCVPriceManager(std::queue<TradingEvent*>&, std::string);
	~OHLCVPriceManager();

	void StreamNextEvent();
	double GetCurrentPrice(std::string);
	bool EOD();
private:
	std::map<boost::gregorian::date, std::vector<OHCLVDataFrame> > InstrumentData;
	std::queue<TradingEvent*>& eventsQueue;
	boost::gregorian::date currentPeriod;
	int readCount = 0;

	void ImportInstrumentData(std::string);

	std::string ConvData(const boost::gregorian::date& date)
	{
		boost::gregorian::date_facet *df = new boost::gregorian::date_facet("%Y%m%d_%H%M%S");

		std::ostringstream is;
		is.imbue(std::locale(is.getloc(), df));
		is << date;

		return is.str();
	}
};

#endif /* DATAHANDLERS_OHLCVPRICEMANAGER_H_ */
