#include "stdafx.h"
#include "Portfolio.h"
//#include "StatisticsManager.h"

Portfolio::Portfolio(double initBalance, std::queue<TradingEvent*>& eventsQueue,
	PriceManager& priceManager) :
	cashBalance(initBalance), initialBalace(initBalance), 
	equity(initBalance), eventsQueue(eventsQueue), priceManager(priceManager) {}

void Portfolio::UpdatePortfolio() {
	unrealisedPnL = 0;
	equity = realisedPnL;
	equity += initialBalace;

	for (auto& element : investedPositions) {
		Position& targetPosition = element.second;

		//TODO: Implement Bid Ask
		double price = priceManager.GetCurrentPrice(element.first);
		double bid = price;
		double ask = price;

		targetPosition.UpdateMarketValue(bid, ask);
		unrealisedPnL += targetPosition.UnRealisedPnL();
		double netPnL = targetPosition.RealisedPnL() - targetPosition.UnRealisedPnL();
		equity += targetPosition.MarketValue() - targetPosition.CostBasis() + netPnL;
	}
}

void Portfolio::UpdateRecords() {
	PriceDataFrame dataFrame = {
		priceManager.GetCurrentTimeStampString(),
		equity
	};
	historicEquity.push_back(dataFrame);
}

void Portfolio::ProcessPosition(std::string ticker, int action, double price, int units, double commission) {

	if (action == 0)
		return;

	//Update the account buying power
	if (action == 1)
		cashBalance -= ((price*units) + commission);
	else if (action == -1)
		cashBalance += ((price*units) - commission);

	if (investedPositions.find(ticker) == investedPositions.end())
		AddPosition(action, ticker, units, price, commission);
	else
		UpdatePosition(action, ticker, units, price, commission);
}

void Portfolio::AddPosition(int action, std::string ticker, int units,
	double price, double commission) {
	//TODO: Implement BID/ASK
	double bid = price;
	double ask = price;

	investedPositions[ticker] = Position(action,
		ticker,
		units,
		price,
		commission,
		bid,
		ask);

	UpdatePortfolio();
}

void Portfolio::UpdatePosition(int action, std::string ticker, int units,
	double price, double commission) {
	investedPositions[ticker].ModifyPosition(action, units, price, commission);

	//TODO: Implement Bid Ask
	double currentPrice = priceManager.GetCurrentPrice(ticker);
	double bid = currentPrice;
	double ask = currentPrice;

	investedPositions[ticker].UpdateMarketValue(bid, ask);

	//Close Position
	if (investedPositions[ticker].Units() == 0) {
		realisedPnL += investedPositions[ticker].RealisedPnL();
		//StatisticsManager::getInstance().UpdatePositionHistory(investedPositions[ticker]);
		investedPositions.erase(ticker);

		std::cout << priceManager.GetCurrentTimeStampString()
			<< " CLOSE position " << ticker << " @ " << price << std::endl;
	}

	UpdatePortfolio();
}

void Portfolio::CloseAllPositions() {
	for (auto const& position : investedPositions) {
		TradingEvent* order = new SignalEvent(position.first,
			position.second.action * -1, position.second.totalUnits);
		eventsQueue.push(order);
	}
}

Portfolio::~Portfolio() {
	// TODO Auto-generated destructor stub
}

std::map<std::string, Position> Portfolio::GetInvestedPositions() const {
	return investedPositions;
}
