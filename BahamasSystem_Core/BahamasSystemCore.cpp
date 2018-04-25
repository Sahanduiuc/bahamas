#include "stdafx.h"
#include "BahamasSystemCore.h"
#include "Strategies\BullPutCreditSpread.h"
#include "Strategies\NetZero.h"

#include "spdlog\spdlog.h"

TradingSession CreateSession() {
	double initEquity = 100000.0;
	std::queue<TradingEvent*> eventsQueue;
	std::vector<std::string> tickers = { "CL" };

	boost::gregorian::date startDate = { 2018, 3, 1 };
	boost::gregorian::date endDate = { 2018, 3, 16 };

	OptionPriceManager priceManager(eventsQueue, "CL", startDate, endDate);
	
	SimulatedExecutionManager executionManager(eventsQueue, priceManager);
	PortfolioManager portfolioManager(initEquity,
		eventsQueue, priceManager);
	NetZero strategy(eventsQueue, tickers, portfolioManager, priceManager);

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

