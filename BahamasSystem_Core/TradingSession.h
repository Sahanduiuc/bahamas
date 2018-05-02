#pragma once

#ifndef TRADINGSESSION_H_
#define TRADINGSESSION_H_

#include <iostream>
#include <queue>

#include "TradingEvent.h"
#include "PriceManager.h"
#include "ExecutionManager.h"
#include "PortfolioManager.h"
#include "Strategy.h"

class TradingSession {
public:
	TradingSession(std::queue<TradingEvent*>& eventsQueue,
		PriceManager& priceManager,
		ExecutionManager& executionManager,
		PortfolioManager& portfolioManager,
		Strategy& strategy);
	//~TradingSession(void);

	void Execute();
private:
	bool isBackTest;
	std::queue<TradingEvent*>& eventsQueue;
	PriceManager& priceManager;
	ExecutionManager& executionManager;
	PortfolioManager& portfolioManager;
	Strategy& strategy;
};

#endif