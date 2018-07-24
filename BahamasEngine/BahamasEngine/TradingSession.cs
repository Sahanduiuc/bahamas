using System;
using System.Collections.Generic;

namespace BahamasEngine
{
    public class TradingSession
    {
        private Queue<TradingEvent> eventsQueue;
        private InstrumentDataManager dataManager;
        private ExecutionManager executionManager;
        private PortfolioManager portfolioManager;
        private StrategyBase strategy;
        private bool terminate = false;

        public TradingSession(Queue<TradingEvent> eventsQueue,
            InstrumentDataManager dataManager,
            ExecutionManager executionManager,
            PortfolioManager portfolioManager,
            StrategyBase strategy
            )
        {
            this.eventsQueue = eventsQueue;
            this.dataManager = dataManager;
            this.executionManager = executionManager;
            this.portfolioManager = portfolioManager;
            this.strategy = strategy;
        }

        public void Execute()
        {
            Console.WriteLine("Starting new Backtest session...");

            while (!dataManager.EOD())
            {
                if (eventsQueue.Count == 0)
                {
                    if (terminate)
                        break;
                    dataManager.StreamNextEvent();
                }
                else
                {
                    TradingEvent tEvent = eventsQueue.Peek();

                    switch (tEvent)
                    {
                        case OptionChainUpdateEvent dataUpdateEvent:
                            portfolioManager.UpdatePortfolioValues();
                            strategy.ExecuteStrategy(dataUpdateEvent);
                            break;
                        case SignalEvent signalEvent:
                            portfolioManager.ProcessSignal(signalEvent);
                            break;
                        case OrderEvent orderEvent:
                            executionManager.ExecuteOrder(orderEvent);
                            break;
                        case FillEvent fillEvent:
                            portfolioManager.ProcessFill(fillEvent);
                            break;
                        case TerminationEvent terminationEvent:
                            terminate = true;
                            break;
                        default:
                            break;
                    }

                    eventsQueue.Dequeue();
                }
            }
            Console.WriteLine("Session completed.");
        }
    }
}
