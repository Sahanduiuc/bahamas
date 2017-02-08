/*
 * Backtest.h
 *
 *  Created on: 11 Nov 2016
 *      Author: shamitha
 */

#ifndef BACKTEST_H_
#define BACKTEST_H_

#include <iostream>
#include <queue>

#include "PriceManager.h"
#include "PortfolioHandler.h"
#include "TradingEvent.h"
#include "Strategy.h"
#include "ExecutionManager.h"
#include "StatisticsManager.h"

class Backtest {
public:
	//TODO complete constructor
	Backtest(PriceManager&, PortfolioHandler&, Strategy&, ExecutionManager&,  
		double, std::queue<TradingEvent*>&);
	virtual ~Backtest();

	void ExecuteBackTest();
private:
	std::queue<TradingEvent*>& eventsQueue;
	PriceManager& priceManager;
	Strategy& strategy;
	PortfolioHandler& portfolioHandler;
	ExecutionManager& executionManager;
};

#endif /* BACKTEST_H_ */
