#ifndef OPTIONPRICEMANAGER_H_
#define OPTIONPRICEMANAGER_H_

#include <queue>
#include <boost/bind.hpp>
#include <boost/filesystem.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"
#include <boost/date_time/gregorian/gregorian_io.hpp>

#include "DataFrames.h"
#include "OptionContract.h"
#include "TradingEvent.h"
#include "PriceManager.h"
#include "DataImporter.h"


class OptionPriceManager : public PriceManager {
public:
	OptionPriceManager(std::queue<TradingEvent*>&,
		std::string ticker,
		boost::gregorian::date&,
		boost::gregorian::date&);
	~OptionPriceManager() {}

	void StreamNextEvent();
	double GetCurrentPrice(std::string);
	bool EOD() { return false; }
	std::string GetCurrentTimeStampString() { return ""; }
	//boost::gregorian::date GetCurrentTimeStamp() const;
private:
	std::map<OptionContract, std::map<std::string, BidAskDataFrame> > InstrumentData;
	std::queue<TradingEvent*>& eventsQueue;
	boost::gregorian::date currentPeriod;
	boost::gregorian::date endPeriod;
	OptionContract activeContract;

	void ImportInstrumentData(std::string);

	boost::gregorian::date ParseDate(const std::string& str)
	{
		std::locale fmt2(std::locale::classic(),
			new boost::gregorian::date_input_facet("%m/%d/%Y"));
		std::istringstream is(str);
		is.imbue(fmt2);
		boost::gregorian::date date;
		is >> date;
		return date;
	}
};

#endif 

