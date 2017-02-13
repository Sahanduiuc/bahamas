/*
 * PortfolioHandler.h
 *
 *  Created on: 6 Nov 2016
 *      Author: shamitha
 */

#ifndef PORTFOLIOHANDLER_H_
#define PORTFOLIOHANDLER_H_

#include "Portfolio.h"
#include "TradingEvent.h"
#include "OrderSizer.h"
#include "RiskManager.h"

#include <queue>

class PortfolioHandler {
public:
	PortfolioHandler(double, std::queue<TradingEvent*>&, PriceManager&);
	virtual ~PortfolioHandler();

	void UpdatePortfolioValue();
	void ProcessSignal(SignalEvent&);
	void ProcessFill(FillEvent&);

	Portfolio GetPortfolio() const;
	double GetPortfolioValue() const {
		return portfolio.GetEquityValue();
	}
private:
	double currentBalance;
	Portfolio portfolio;
	OrderSizer orderSizer;
	RiskManager riskManager;
	PriceManager& priceManager;
	std::queue<TradingEvent*>& eventsQueue;
};

#endif /* PORTFOLIOHANDLER_H_ */
