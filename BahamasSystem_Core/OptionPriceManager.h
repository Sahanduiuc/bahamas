#ifndef OPTIONPRICEMANAGER_H_
#define OPTIONPRICEMANAGER_H_

#include <queue>
#include <boost/bind.hpp>
#include <boost/filesystem.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"

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
	std::map<OptionContract, std::map<boost::gregorian::date, BidAskDataFrame> > InstrumentData;
	std::queue<TradingEvent*>& eventsQueue;
	boost::gregorian::date currentPeriod;
	boost::gregorian::date endPeriod;
	OptionContract activeContract;

	void ImportInstrumentData(std::string);
};

#endif 

