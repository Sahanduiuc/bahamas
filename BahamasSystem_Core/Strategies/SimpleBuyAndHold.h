#pragma once

#include "..\Strategy.h"

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



