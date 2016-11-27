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

class PortfolioManager {
public:
	PortfolioManager(double, std::queue<TradingEvent*>&);
	virtual ~PortfolioManager();

	void UpdatePortfolioValue();
	void ProcessSignal(SignalEvent&);
private:
	double currentBalance;
	Portfolio portfolio;
	OrderSizer orderSizer;
	RiskManager riskManager;
	std::queue<TradingEvent*>& eventsQueue;
};

#endif /* PORTFOLIOHANDLER_H_ */
