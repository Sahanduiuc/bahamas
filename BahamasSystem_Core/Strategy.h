#ifndef STRATEGY_H_
#define STRATEGY_H_

#include <queue>
#include <numeric>
#include <map>
#include <unordered_set>

#include "TradingEvent.h"
#include "OHLCVPriceManager.h"
#include "boost/date_time/gregorian/gregorian.hpp"

class Strategy {
public:
	const std::vector<std::string> tickers;

	Strategy(std::queue<TradingEvent*>& eventsQueue, std::vector<std::string> tickers) :
		eventsQueue(eventsQueue), tickers(tickers) {};
	virtual void CalculateSignal(BarEvent& event) = 0;
protected:
	std::queue<TradingEvent*>& eventsQueue;
};

#endif