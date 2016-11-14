/*
 * PortfolioHandler.h
 *
 *  Created on: 6 Nov 2016
 *      Author: shamitha
 */

#ifndef PORTFOLIOHANDLER_H_
#define PORTFOLIOHANDLER_H_

class PortfolioHandler {
public:
	PortfolioHandler(double initialBalance):currentBalance(initialBalance) {}
	virtual ~PortfolioHandler();
private:
	double currentBalance;

};

#endif /* PORTFOLIOHANDLER_H_ */
