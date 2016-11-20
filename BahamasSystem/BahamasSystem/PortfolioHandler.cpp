/*
 * PortfolioHandler.cpp
 *
 *  Created on: 6 Nov 2016
 *      Author: shamitha
 */

#include "PortfolioHandler.h"

PortfolioHandler::PortfolioHandler(double initialBalance) :
	currentBalance(initialBalance), portfolio(Portfolio(initialBalance)) {
}

PortfolioHandler::~PortfolioHandler() {
	// TODO Auto-generated destructor stub
}

void PortfolioHandler::UpdatePortfolioValue() {
	portfolio.UpdatePortfolio();
}

void PortfolioHandler::ProcessSignal(TradingEvent& event) {

}
