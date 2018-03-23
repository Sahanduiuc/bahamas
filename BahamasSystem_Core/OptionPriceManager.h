#ifndef OPTIONPRICEMANAGER_H_
#define OPTIONPRICEMANAGER_H_

#include <queue>
#include <boost/bind.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"

#include "TradingEvent.h"
#include "PriceManager.h"

class OptionPriceManager : public PriceManager {
public:
	OptionPriceManager(std::queue<TradingEvent*>&,
		std::string ticker,
		boost::gregorian::date&,
		boost::gregorian::date&);
	~OptionPriceManager() {}

	void StreamNextEvent() {}
	//double GetCurrentPrice(std::string) {}
	bool EOD() { return false; }
	//std::string GetCurrentTimeStampString() {}
	//boost::gregorian::date GetCurrentTimeStamp() const {}
private:
	std::queue<TradingEvent*>& eventsQueue;
	boost::gregorian::date currentPeriod;
	boost::gregorian::date endPeriod;

	void ImportInstrumentData(std::string);
};

#endif 

