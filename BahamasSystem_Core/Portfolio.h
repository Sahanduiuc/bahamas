#ifndef PORTFOLIO_H_
#define PORTFOLIO_H_

#include <string>
#include <map>
#include <algorithm>
#include <iostream>

#include "Position.h"
#include "PriceManager.h"

class Portfolio {
public:
	Portfolio(double, PriceManager&);
	virtual ~Portfolio();

	void UpdatePortfolio();
	void ProcessPosition(std::string, int, double, int, double);
	std::map<std::string, Position> GetInvestedPositions() const;
	double GetEquityValue() const {
		return equity;
	}
private:
	double cashBalance = 0.0;
	double initialBalace = 0.0;
	double realisedPnL = 0.0;
	double unrealisedPnL = 0.0;
	double equity = 0.0;
	PriceManager& priceManager;
	std::map<std::string, Position> investedPositions;

	void AddPosition(int, std::string, int, double, double);
	void UpdatePosition(int, std::string, int, double, double);
};

#endif
