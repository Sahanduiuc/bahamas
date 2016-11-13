//============================================================================
// Name        : BahamasSystem.cpp
// Author      : Shamitha
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <queue>

#include "Backtest.h"
#include "OHLCVPriceManager.h"

using namespace std;

int main() {

	double initEquity = 1000.0;

	std::queue<TradingEvent> eventsQueue;
	OHLCVPriceManager priceManager(eventsQueue, "msft");
	PortfolioHandler portfolioHandler(initEquity);

	Backtest testBackTest(
			priceManager,
			portfolioHandler,
			initEquity,
			eventsQueue);

	testBackTest.ExecuteBackTest();

	return 0;
}
