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

class Backtest {
public:
	//TODO complete constructor
	Backtest(PriceManager&, PortfolioManager&, Strategy&,  
		double, std::queue<TradingEvent*>&);
	virtual ~Backtest();

	void ExecuteBackTest();
private:
	std::queue<TradingEvent*>& eventsQueue;
	PriceManager& priceManager;
	Strategy& strategy;
	PortfolioManager& portfolioHandler;
};

#endif /* BACKTEST_H_ */
