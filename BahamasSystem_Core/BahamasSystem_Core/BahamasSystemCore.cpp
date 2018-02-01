#include "stdafx.h"
#include "BahamasSystemCore.h"

TradingSession CreateSession() {
	double initEquity = 100000.0;
	std::queue<TradingEvent*> eventsQueue;
	std::vector<std::string> tickers = { "NVDA" };

	boost::gregorian::date startDate = { 2014, 11, 01 };
	boost::gregorian::date endDate = { 2017, 02, 01 };

	OHLCVPriceManager priceManager(eventsQueue, tickers,
		startDate,endDate);
	SimulatedExecutionManager executionManager(eventsQueue, priceManager);
	PortfolioManager portfolioManager(initEquity,
		eventsQueue, priceManager);
	SimpleBuyHold strategy(eventsQueue, tickers);

	auto session = TradingSession(eventsQueue, 
		priceManager,
		executionManager,
		portfolioManager,
		strategy);
	session.Execute();

	return session;
}

std::string ExecuteSession(TradingSession* session) {
	session->Execute();
	return "Test";
}

