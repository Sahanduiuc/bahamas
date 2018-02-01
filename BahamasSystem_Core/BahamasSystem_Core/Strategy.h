#ifndef STRATEGY_H_
#define STRATEGY_H_

#include <queue>
#include <numeric>
#include <map>
#include <unordered_set>

#include "TradingEvent.h"
#include "OHLCVPriceManager.h"

class Strategy {
public:
	const std::vector<std::string> tickers;

	Strategy(std::queue<TradingEvent*>& eventsQueue, std::vector<std::string> tickers) :
		eventsQueue(eventsQueue), tickers(tickers) {};
	virtual void CalculateSignal(BarEvent& event) = 0;
protected:
	std::queue<TradingEvent*>& eventsQueue;
};

class SimpleBuyHold : public Strategy {
public:
	SimpleBuyHold(std::queue<TradingEvent*>& eventsQueue, 
		std::vector<std::string> tickers) :
		Strategy(eventsQueue, tickers) {
		for (auto ticker : tickers) {
			investedStatus[ticker] = false;
		}
	}
	void CalculateSignal(BarEvent& event) {
		if (!investedStatus[event.GetEventTicker()]) {
			//Open Long position
			TradingEvent* tempEvent = new SignalEvent(event.GetEventTicker(), 1, 1);
			eventsQueue.push(tempEvent);
			investedStatus[event.GetEventTicker()] = true;
		}
	}

private:
	std::map<std::string, bool> investedStatus;
};

#endif