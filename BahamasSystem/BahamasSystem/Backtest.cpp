/*
 * Backtest.cpp
 *
 *  Created on: 11 Nov 2016
 *      Author: shamitha
 */

#include "Backtest.h"

Backtest::Backtest(PriceManager& priceManager, PortfolioHandler& portfolioHandler,
		Strategy& strategy,double initEquity, std::queue<TradingEvent*>& eventsQueue):
		eventsQueue(eventsQueue), priceManager(priceManager), strategy(strategy), portfolioHandler(portfolioHandler) {
	// TODO Auto-generated constructor stub
}

void Backtest::ExecuteBackTest(){

	int temp = 1000;
	//TODO change terminate condition
	while(!temp <= 0){

		//If the Events queue is empty then wait for more price data
		if(eventsQueue.empty()){
			priceManager.StreamNextEvent();
			temp--;
		}else{
			TradingEvent* event = eventsQueue.front();

			switch(event->GetEventType()){
				case EventType::BarEventType : {
					BarEvent& tempEvent = dynamic_cast<BarEvent&>(*event);
					double price = tempEvent.AdjClose;
					strategy.CalculateSignal(tempEvent);
					///TODO: Implement Update Portfolio 
					portfolioHandler.UpdatePortfolioValue();
					break;
				}
				case EventType::OrderEventType : {
					//OrderEvent& tempEvent = dynamic_cast<OrderEvent&>(event);
					break;
				}
				case EventType::SignalEventType : {
					SignalEvent& tempEvent = dynamic_cast<SignalEvent&>(*event);
					portfolioHandler.ProcessSignal(tempEvent);
					break;
				}
				case EventType::BaseEventType :
					break;
			}

			//TODO Mem leak test
			delete event;
			eventsQueue.pop();
		}
	}
	std::cout << "Backtest Finished";
}

Backtest::~Backtest() {
	// TODO Auto-generated destructor stub
}
