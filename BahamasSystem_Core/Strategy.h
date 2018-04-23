#ifndef STRATEGY_H_
#define STRATEGY_H_

#include <queue>
#include <numeric>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include "float.h"

#include "TradingEvent.h"
#include "OHLCVPriceManager.h"
#include "boost/date_time/gregorian/gregorian.hpp"

class Strategy {
public:
	const std::vector<std::string> tickers;

	Strategy(std::queue<TradingEvent*>& eventsQueue, std::vector<std::string> tickers) :
		eventsQueue(eventsQueue), tickers(tickers) {};
	virtual void CalculateSignal(BarEvent& event) {}
	virtual void CalculateSignal(OptionChainUpdateEvent& event) {}
protected:
	std::queue<TradingEvent*>& eventsQueue;
};

std::vector<OptionContract*> GetSpread(OptionChain* optionChain, double width,
	double targetValue, char type);
OptionChain* GetFurthestDteChain(int maxDte, std::vector<OptionChain*>& optionChains);
OptionContract* GetDeltaTargetContract(OptionChain* optionChain,
	double delta, char optionType);

#endif