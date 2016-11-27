//============================================================================
// Name        : BahamasSystem.cpp
// Author      : Shamitha
// Version     :
// Copyright   : Your copyright notice
// Description : Bahamas Trading System
//============================================================================

#include <iostream>
#include <queue>

#include "Backtest.h"
#include "OHLCVPriceManager.h"
#include "Strategy.h"

using namespace std;

int main() {

	double initEquity = 1000.0;
	std::queue<TradingEvent*> eventsQueue;
	const std::vector<std::string> tickers = { "nvda" };

	OHLCVPriceManager priceManager(eventsQueue, "nvda");
	PortfolioManager portfolioHandler(initEquity, eventsQueue);
	TestStrategy testStrategy(eventsQueue, tickers);

	Backtest testBackTest(
			priceManager,
			portfolioHandler,
			testStrategy,
			initEquity,
			eventsQueue);

	testBackTest.ExecuteBackTest();

	return 0;
}
