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
#include "ExecutionManager.h"

using namespace std;

int main() {

	double initEquity = 1000.0;
	std::queue<TradingEvent*> eventsQueue;
	const std::vector<std::string> tickers = { "dis" };

	OHLCVPriceManager priceManager(eventsQueue, "dis");
	SimulatedExecutionManager executionManager(eventsQueue,priceManager);
	PortfolioManager portfolioHandler(initEquity, eventsQueue, priceManager);
	SimpleMomentum testStrategy(eventsQueue, tickers);
	
	Backtest testBackTest(
			priceManager,
			portfolioHandler,
			testStrategy,
			executionManager,
			initEquity,
			eventsQueue);

	testBackTest.ExecuteBackTest();

	return 0;
}
