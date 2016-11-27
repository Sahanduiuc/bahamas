/*
 * Portfolio.cpp
 *
 *  Created on: 6 Nov 2016
 *      Author: shamitha
 */

#include "Portfolio.h"

Portfolio::Portfolio(double initBalance, PriceManager& priceManager) :
	cashBalance(initBalance),initialBalace(initBalance),equity(initBalance), priceManager(priceManager) {}

void Portfolio::UpdatePortfolio(){
	unrealisedPnL = 0;
	equity += (realisedPnL + initialBalace);

	for (auto& element : investedPositions) {
		Position& targetPosition = element.second;

		//TODO: Implement Bid Ask
		double price = priceManager.GetCurrentPrice(element.first);
		double bid = price;
		double ask = price;

		targetPosition.UpdateMarketValue(bid, ask);
	}
}

void Portfolio::ProcessPosition(std::string ticker, int action, double price,int units, double commission){
	
	if (action == 0)
		return;
	
	//Update the account buying power
	if (action == 1)
		cashBalance -= ((price*units) + commission);
	else if (action == -1)
		cashBalance += ((price*units) - commission);

	if (investedPositions.find(ticker) == investedPositions.end() )
		AddPosition(action, ticker, units, price, commission);
	else
		UpdatePosition(action, ticker, units, price, commission);
}

void Portfolio::AddPosition(int action, std::string ticker, int units,
	double price, double commission) {
	//TODO: Implement BID/ASK
	double bid = price;
	double ask = price;

	investedPositions[ticker] = Position(action,
		ticker,
		units,
		price,
		commission,
		bid,
		ask);

	UpdatePortfolio();
}

void Portfolio::UpdatePosition(int action, std::string ticker, int units,
			double price, double commission){

}

Portfolio::~Portfolio() {
	// TODO Auto-generated destructor stub
}

