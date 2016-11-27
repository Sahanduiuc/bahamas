#ifndef EXECUTIONMANAGER_H_
#define EXECUTIONMANAGER_H_

#include "TradingEvent.h"
#include "PriceManager.h"

#include <queue>

class ExecutionManager {
public:
	ExecutionManager(std::queue<TradingEvent*>& eventsQueue, PriceManager& priceManager):
		eventsQueue(eventsQueue), priceManager(priceManager) {}

	virtual void ExecuteOrder(OrderEvent&) = 0;

protected:
	std::queue<TradingEvent*>& eventsQueue;
	PriceManager& priceManager;
};

class SimulatedExecutionManager : public ExecutionManager {
public:
	SimulatedExecutionManager(std::queue<TradingEvent*>& eventsQueue, PriceManager& priceManager):
		ExecutionManager(eventsQueue, priceManager) {}

	void ExecuteOrder(OrderEvent& event) {
		//TODO: Implement BID/ASK
		double commission = GetCommission(event);

		FillEvent* tempEvent = new FillEvent(
			event.GetEventTicker(),
			event.Action,
			event.OrderUnits,
			priceManager.GetCurrentPrice(event.GetEventTicker()),
			commission
		);

		eventsQueue.push(tempEvent);
	}
private:
	//TODO: Add Trade Transaction cost
	double GetCommission(OrderEvent& event) const {
		return 0.0;
	}
};

#endif
