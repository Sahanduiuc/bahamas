#ifndef OHLCVPRICEMANAGER_H_
#define OHLCVPRICEMANAGER_H_

#include <queue>
#include <boost/bind.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"

#include "DataFrames.h"
#include "TradingEvent.h"
#include "PriceManager.h"
#include "DataImporter.h"

class OHLCVPriceManager : public PriceManager {
public:
	OHLCVPriceManager(std::queue<TradingEvent*>&,
		std::vector<std::string>,
		boost::gregorian::date&,
		boost::gregorian::date&);
	~OHLCVPriceManager();

	void StreamNextEvent();
	double GetCurrentPrice(std::string);
	bool EOD();
	std::string GetCurrentTimeStampString();
	boost::gregorian::date GetCurrentTimeStamp() const;
private:
	std::map<boost::gregorian::date,std::vector<OHCLVDataFrame> > InstrumentData;
	std::queue<TradingEvent*>& eventsQueue;
	boost::gregorian::date currentPeriod;
	boost::gregorian::date endPeriod;
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

#endif