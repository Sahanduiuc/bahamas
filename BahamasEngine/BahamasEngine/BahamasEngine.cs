using BahamasEngine.Strategies;
using System.Collections.Generic;

namespace BahamasEngine
{
    public class BahamasEngine
    {
        private const string ticker = "CL";
        private const double initialEquity = 100000.0;
        private Queue<TradingEvent> eventsQueue;
        private InstrumentDataManager dataManager;
        private ExecutionManager executionManager;
        private PortfolioManager portfolioManager;
        private StrategyBase strategy;
        private TradingSession session;

        public BahamasEngine()
        {
            eventsQueue = new Queue<TradingEvent>();
            dataManager = new InstrumentDataManager(ticker, ref eventsQueue);
            executionManager = new SimulatedExecutionManager(eventsQueue, dataManager);
            portfolioManager = new PortfolioManager(eventsQueue, dataManager, initialEquity);
            strategy = new NetZero(eventsQueue, dataManager, portfolioManager);

            session = new TradingSession(
                eventsQueue,
                dataManager,
                executionManager,
                portfolioManager,
                strategy);
        }

        public void Execute()
        {
            session.Execute();
        }
    }
}
