#ifndef EXECUTIONMANAGER_H_
#define EXECUTIONMANAGER_H_

#include "TradingEvent.h"
#include "PriceManager.h"
#include "Logger.h"

#include <iostream>
#include <queue>

class ExecutionManager {
public:
	ExecutionManager(std::queue<TradingEvent*>& eventsQueue,
		PriceManager& priceManager):
		eventsQueue(eventsQueue), priceManager(priceManager) {}

	virtual void ExecuteOrder(OrderEvent&) = 0;
protected:
	std::queue<TradingEvent*>& eventsQueue;
	PriceManager& priceManager;
};

class SimulatedExecutionManager : public ExecutionManager {
public:
	SimulatedExecutionManager(std::queue<TradingEvent*>& eventsQueue, 
		PriceManager& priceManager):
		ExecutionManager(eventsQueue, priceManager){}

	void ExecuteOrder(OrderEvent& event) {
		//TODO: use mid price from bid/ask
		double commission = GetCommission(event);

		FillEvent* tempEvent = new FillEvent(
			event.GetEventTicker(),
			event.Action,
			event.OrderUnits,
			priceManager.GetCurrentPrice(event.GetEventTicker()),
			commission,
			event.tradeId
		);

		//Log Trade execution
		ExecutionDataFrame dataframe{
			priceManager.GetCurrentTimeStampString(),
			event.GetEventTicker(),
			event.tradeId
		};
		Logger::instance().ExecutionData.push_back(dataframe);

		eventsQueue.push(tempEvent);
	}
private:
	//TODO: Add transaction costs
	double GetCommission(OrderEvent& event) const {
		return event.OrderUnits * 2.35;
	}
};

#endif