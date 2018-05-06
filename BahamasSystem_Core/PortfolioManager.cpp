#include "stdafx.h"
#include "PortfolioManager.h"

PortfolioManager::PortfolioManager(double initialBalance, std::queue<TradingEvent*>& eventsQueue, PriceManager& priceManager) :
	currentBalance(initialBalance), eventsQueue(eventsQueue), 
	portfolio(Portfolio(initialBalance, eventsQueue, priceManager)), 
	priceManager(priceManager) {

}

PortfolioManager::~PortfolioManager() {
	// TODO Auto-generated destructor stub
}

void PortfolioManager::UpdatePortfolioValue() {
	portfolio.UpdatePortfolio();
}

void PortfolioManager::ProcessSignal(SignalEvent& event) {
	MarketOrder order = { event.GetEventTicker(),
		event.action,
		event.setOrderUnits, 
		priceManager.GetCurrentPrice(event.GetEventTicker()) 
	};
	orderSizer.SizeOrder(order, portfolio);
	std::vector<MarketOrder> profiledOrders = riskManager.ProfileOrder(order);

	//Place Order on Events queue for execution
	for (MarketOrder& curOrder : profiledOrders) {
		OrderEvent* o_event = new OrderEvent(curOrder.Ticker,
			curOrder.Action,
			curOrder.Units,
			event.tradeId);

		eventsQueue.push(o_event);
	}
}

void PortfolioManager::ProcessFill(FillEvent& event) {
	portfolio.ProcessPosition(
		event.GetEventTicker(),
		event.Action,
		event.FillPrice,
		event.Units,
		event.Commission,
		event.tradeId);
}

Portfolio PortfolioManager::GetPortfolio() const {
	return portfolio;
}
