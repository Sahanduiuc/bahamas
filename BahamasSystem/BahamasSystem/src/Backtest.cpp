/*
 * Backtest.cpp
 *
 *  Created on: 11 Nov 2016
 *      Author: shamitha
 */

#include "Backtest.h"

Backtest::Backtest(PriceManager priceManager, PortfolioHandler portfolioHandler,
		double initEquity, std::queue<TradingEvent>& eventsQueue):
		eventsQueue(eventsQueue) {
	// TODO Auto-generated constructor stub

}

void Backtest::ExecuteBackTest(){

	//TODO change terminate condition
	while(!true){
		TradingEvent event = eventsQueue.front();

		switch(event.GetEventType()){
			case EventType::BarEvent :
				break;
			case EventType::OrderEvent :
				break;
			case EventType::SignalEvent :
				break;
			case EventType::Event :
				break;
		}

		eventsQueue.pop();
	}

}

Backtest::~Backtest() {
	// TODO Auto-generated destructor stub
}

