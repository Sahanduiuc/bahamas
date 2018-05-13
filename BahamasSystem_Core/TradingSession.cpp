#include "stdafx.h"
#include "TradingSession.h"
#include "Logger.h"
#include "Strategy.h"

TradingSession::TradingSession(std::queue<TradingEvent*>& eventsQueue,
	OptionPriceManager& priceManager,
	ExecutionManager& executionManager,
	PortfolioManager& portfolioManager,
	Strategy& strategy):
	eventsQueue(eventsQueue),
	priceManager(priceManager),
	executionManager(executionManager),
	portfolioManager(portfolioManager),
	strategy(strategy)
{
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
					portfolioManager.UpdatePortfolioValue();
					strategy.CalculateSignal(tempEvent);
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
					break;
				}
				case EventType::BaseEventType:
					break;
			}

			delete t_event;
			eventsQueue.pop();

			//Update metrics at end of each trading timestamp
			if (eventsQueue.empty()) {
				PriceDataFrame dataFrame = {
					priceManager.GetCurrentTimeStampString(),
					portfolioManager.GetPortfolioValue()
				};
				Logger::instance().PortfolioData.push_back(dataFrame);

				std::map<std::string, Position> positions = 
					portfolioManager.GetPortfolio().GetInvestedPositions();
				for (auto const& kv_pair : positions) {
					Logger::instance().ContractMarketData[kv_pair.first].push_back(
						priceManager.GetCurrentDataFrame(kv_pair.first)
					);
				}
			}
		}
	}
	
	Logger::instance().ConsoleLog("Session Ended.");
	Logger::instance().ExportBacktestResults();
}