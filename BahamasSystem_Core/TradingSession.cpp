#include "stdafx.h"
#include "TradingSession.h"

TradingSession::TradingSession(std::queue<TradingEvent*>& eventsQueue,
	PriceManager& priceManager,
	ExecutionManager& executionManager,
	PortfolioManager& portfolioManager,
	Strategy& strategy):
	eventsQueue(eventsQueue),
	priceManager(priceManager),
	executionManager(executionManager),
	portfolioManager(portfolioManager),
	strategy(strategy)
{
	int i = 9;
}

void TradingSession::Execute() {

	std::cout << "Starting Backtest session..." << std::endl;
	//TODO change terminate condition
	while (!priceManager.EOD()) {
		//If the Events queue is empty then wait for a price event
		if (eventsQueue.empty()) {
			priceManager.StreamNextEvent();
		}
		else {
			TradingEvent* t_event = eventsQueue.front();

			switch (t_event->GetEventType()) {
				case EventType::OptionChainUpdateEventType: {
					OptionChainUpdateEvent& tempEvent = static_cast<OptionChainUpdateEvent&>(*t_event);
					strategy.CalculateSignal(tempEvent);
					portfolioManager.UpdatePortfolioValue();
					break;
				}
				case EventType::OrderBookUpdateEventType: {
					OrderBookUpdateEvent& tempEvent = static_cast<OrderBookUpdateEvent&>(*t_event);
					break;
				}
				case EventType::OrderEventType: {
					OrderEvent& tempEvent = static_cast<OrderEvent&>(*t_event);
					executionManager.ExecuteOrder(tempEvent);
					break;
				}
				case EventType::SignalEventType: {
					SignalEvent& tempEvent = static_cast<SignalEvent&>(*t_event);
					portfolioManager.ProcessSignal(tempEvent);
					break;
				}
				case EventType::FillEventType: {
					FillEvent& tempEvent = static_cast<FillEvent&>(*t_event);
					portfolioManager.ProcessFill(tempEvent);
					StatisticsManager::getInstance().UpdateTradeHistory(tempEvent);
					break;
				}
				case EventType::BaseEventType:
					break;
			}

			//TODO Mem leak test
			delete t_event;
			eventsQueue.pop();
		}
	}
	//StatisticsManager::getInstance().GenerateTearSheetData();
	std::cout << "Session Ended." << std::endl;
	std::cout << portfolioManager.GetPortfolioValue() << std::endl;
}