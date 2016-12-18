#ifndef EXECUTIONMANAGER_H_
#define EXECUTIONMANAGER_H_

#include "TradingEvent.h"
#include "PriceManager.h"

#include <iostream>
#include <fstream>  
#include <queue>
#include <ctime>
#include <string>
#include <sstream>

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

class InvestopediaExecutionManager : public ExecutionManager {
public:
	InvestopediaExecutionManager(std::queue<TradingEvent*>& eventsQueue, PriceManager& priceManager) :
		ExecutionManager(eventsQueue, priceManager) {}

	void ExecuteOrder(OrderEvent& event) {
		
		FillEvent* tempEvent = new FillEvent(
			event.GetEventTicker(),
			event.Action,
			event.OrderUnits,
			priceManager.GetCurrentPrice(event.GetEventTicker()),
			0.0
		);

		eventsQueue.push(tempEvent);
		
		time_t t = time(0);   // get time now
		struct tm * now = localtime(&t);
		std::stringstream dateStream;
		dateStream << (now->tm_year + 1900) << '-'
			<< (now->tm_mon + 1) << '-'
			<< now->tm_mday;

		std::string path(getenv("HOME"));
		path += "/Desktop/orders/" + dateStream.str() + ".txt";
		std::ofstream outfile(path);

		std::string order = event.GetEventTicker() + "," + std::to_string(event.Action) + "," + std::to_string(event.OrderUnits);
		outfile << order;
		outfile.close();

		std::cout << "New order file created." << std::endl;
	}
private:
};

#endif
