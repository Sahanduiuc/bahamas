/*
 * PortfolioHandler.cpp
 *
 *  Created on: 6 Nov 2016
 *      Author: shamitha
 */

#include "PortfolioHandler.h"

PortfolioHandler::PortfolioHandler(double initialBalance, std::queue<TradingEvent*>& eventsQueue, PriceManager& priceManager) :
	currentBalance(initialBalance), eventsQueue(eventsQueue), portfolio(Portfolio(initialBalance,priceManager)) {
	
}

PortfolioHandler::~PortfolioHandler() {
	// TODO Auto-generated destructor stub
}

void PortfolioHandler::UpdatePortfolioValue() {
	portfolio.UpdatePortfolio();
}

void PortfolioHandler::ProcessSignal(SignalEvent& event) {
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

void PortfolioHandler::ProcessFill(FillEvent& event) {
	portfolio.ProcessPosition(
		event.GetEventTicker(),
		event.Action,
		event.FillPrice,
		event.Units,
		event.Commission);
}

Portfolio PortfolioHandler::GetPortfolio() const {
	return portfolio;
}
