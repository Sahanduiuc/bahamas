/*
 * Portfolio.h
 *
 *  Created on: 6 Nov 2016
 *      Author: shamitha
 */

#ifndef PORTFOLIO_H_
#define PORTFOLIO_H_

#include <string>
#include <map>
#include <algorithm>

#include "Position.h"
#include "PriceManager.h"

class Portfolio {
public:
	Portfolio(double, PriceManager&);
	virtual ~Portfolio();

	void UpdatePortfolio();
	void ProcessPosition(std::string,int,double,int,double);
private:
	double cashBalance;
	double initialBalace;
	double realisedPnL;
	double unrealisedPnL;
	double equity;
	PriceManager& priceManager;
	std::map<std::string,Position> investedPositions;

	void AddPosition(int, std::string, int, double, double);
	void UpdatePosition(int, std::string, int, double, double);
};

#endif /* PORTFOLIO_H_ */
