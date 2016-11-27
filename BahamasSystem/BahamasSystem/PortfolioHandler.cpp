/*
 * PortfolioHandler.cpp
 *
 *  Created on: 6 Nov 2016
 *      Author: shamitha
 */

#include "PortfolioHandler.h"

PortfolioManager::PortfolioManager(double initialBalance, std::queue<TradingEvent*>& eventsQueue) :
	currentBalance(initialBalance), eventsQueue(eventsQueue), portfolio(Portfolio(initialBalance)) {
	
}

PortfolioManager::~PortfolioManager() {
	// TODO Auto-generated destructor stub
}

void PortfolioManager::UpdatePortfolioValue() {
	portfolio.UpdatePortfolio();
}

void PortfolioManager::ProcessSignal(SignalEvent& event) {
	MarketOrder order = { event.GetEventTicker(),event.action,
		event.setOrderUnits };
	orderSizer.SizeOrder(order);
	std::vector<MarketOrder> profiledOrders = riskManager.ProfileOrder(order);

	//Place Order on Events queue for execution
	for (MarketOrder& curOrder : profiledOrders) {
		OrderEvent* event = new OrderEvent(curOrder.Ticker,
			curOrder.Action,
			curOrder.Units);

		eventsQueue.push(event);
	}
}
