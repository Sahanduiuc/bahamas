#include "stdafx.h"
#include "BahamasSystemCore.h"
#include "Strategies\BullPutCreditSpread.h"

TradingSession CreateSession() {
	double initEquity = 100000.0;
	std::queue<TradingEvent*> eventsQueue;
	std::vector<std::string> tickers = { "ES" };

	boost::gregorian::date startDate = { 2016, 11, 01 };
	boost::gregorian::date endDate = { 2017, 12, 01 };

	//OHLCVPriceManager priceManager(eventsQueue, tickers,startDate,endDate);
	OptionPriceManager priceManager(eventsQueue, "ES", startDate, endDate);
	
	SimulatedExecutionManager executionManager(eventsQueue, priceManager);
	PortfolioManager portfolioManager(initEquity,
		eventsQueue, priceManager);
	BullPutCreditSpread strategy(eventsQueue, tickers);

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

