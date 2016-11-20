/*
 * Portfolio.h
 *
 *  Created on: 6 Nov 2016
 *      Author: shamitha
 */

#ifndef PORTFOLIO_H_
#define PORTFOLIO_H_

#include <string>

class Portfolio {
public:
	Portfolio(double);
	virtual ~Portfolio();

	void UpdatePortfolio();
	void AddPosition(int, std::string, int, double, double);
	void UpdatePosition(int, std::string, int, double, double);

private:
	double currentBalance;
	double realisedPnL;
	//std::vector<> positions;
};

#endif /* PORTFOLIO_H_ */
