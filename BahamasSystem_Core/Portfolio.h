#ifndef PORTFOLIO_H_
#define PORTFOLIO_H_

#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>

#include "DataFrames.h"
#include "Position.h"
#include "PriceManager.h"
#include "TradingEvent.h"

class Portfolio {
public:
	Portfolio(double, std::queue<TradingEvent*>&, PriceManager&);
	virtual ~Portfolio();

	void UpdatePortfolio();
	void ProcessPosition(std::string, int, double, int, double, int);
	void CloseAllPositions();
	std::map<std::string, Position> GetInvestedPositions() const;
	double GetEquityValue() const {
		return equity;
	}
	double GetUnrealisedPnL() const {
		return unrealisedPnL;
	}

private:
	double cashBalance = 0.0;
	double initialBalace = 0.0;
	double realisedPnL = 0.0;
	double unrealisedPnL = 0.0;
	double equity = 0.0;
	PriceManager& priceManager;
	std::map<std::string, Position> investedPositions;
	std::queue<TradingEvent*>& eventsQueue;

	void AddPosition(int, std::string, int, double, double, int);
	void UpdatePosition(int, std::string, int, double, double);
};

#endif
