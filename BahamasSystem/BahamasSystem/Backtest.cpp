/*
 * Backtest.cpp
 *
 *  Created on: 11 Nov 2016
 *      Author: shamitha
 */

#include "Backtest.h"

Backtest::Backtest(PriceManager& priceManager, PortfolioHandler& portfolioHandler,
		Strategy& strategy,ExecutionManager& executionManager, double initEquity, std::queue<TradingEvent*>& eventsQueue):
		eventsQueue(eventsQueue), priceManager(priceManager), strategy(strategy), portfolioHandler(portfolioHandler), executionManager(executionManager) {
	// TODO Auto-generated constructor stub
}

void Backtest::ExecuteBackTest(){

	//TODO change terminate condition
	while(!priceManager.EOD()){
		//If the Events queue is empty then wait for more price data
		if(eventsQueue.empty()){
			priceManager.StreamNextEvent();
		}else{
			TradingEvent* event = eventsQueue.front();

			switch(event->GetEventType()){
				case EventType::BarEventType : {
					BarEvent& tempEvent = dynamic_cast<BarEvent&>(*event);
					strategy.CalculateSignal(tempEvent);
					portfolioHandler.UpdatePortfolioValue();
					StatisticsManager::getInstance().UpdateEquityCurve(portfolioHandler,
						priceManager);
					break;
				}
				case EventType::OrderEventType : {
					OrderEvent& tempEvent = dynamic_cast<OrderEvent&>(*event);
					executionManager.ExecuteOrder(tempEvent);
					break;
				}
				case EventType::SignalEventType : {
					SignalEvent& tempEvent = dynamic_cast<SignalEvent&>(*event);
					portfolioHandler.ProcessSignal(tempEvent);
					break;
				}
				case EventType::FillEventType: {
					FillEvent& tempEvent = dynamic_cast<FillEvent&>(*event);
					portfolioHandler.ProcessFill(tempEvent);
					StatisticsManager::getInstance().UpdateTradeHistory(tempEvent);
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

	//auto v1 = StatisticsManager::getInstance().GetTradeCount();
	//auto v2 = StatisticsManager::getInstance().GetStrategyAccuracy();
	StatisticsManager::getInstance().GenerateTearSheetData();

	std::cout << "Backtest Complete.";
}

Backtest::~Backtest() {
	// TODO Auto-generated destructor stub
}

