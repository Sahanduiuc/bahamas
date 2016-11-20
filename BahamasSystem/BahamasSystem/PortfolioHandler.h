/*
 * PortfolioHandler.h
 *
 *  Created on: 6 Nov 2016
 *      Author: shamitha
 */

#ifndef PORTFOLIOHANDLER_H_
#define PORTFOLIOHANDLER_H_

#include "Portfolio.h"
#include "TradingEvent.h"

class PortfolioHandler {
public:
	PortfolioHandler(double);
	virtual ~PortfolioHandler();

	void UpdatePortfolioValue();
	void ProcessSignal(TradingEvent&);
private:
	double currentBalance;
	Portfolio portfolio;
};

#endif /* PORTFOLIOHANDLER_H_ */
