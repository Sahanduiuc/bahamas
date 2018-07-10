using BahamasEngine.Strategies;
using System.Collections.Generic;

namespace BahamasEngine
{
    public class BahamasEngine
    {
        private enum BackTestType
        {
            Continuous,
            Standard
        };

        private const string ticker = "CL";
        private const double initialEquity = 100000.0;
        private Queue<TradingEvent> eventsQueue = new Queue<TradingEvent>();
        private InstrumentDataManager dataManager;
        private ExecutionManager executionManager;
        private PortfolioManager portfolioManager;
        private StrategyBase strategy;
        private TradingSession session;
        private BackTestType backTestType = BackTestType.Continuous;

        public BahamasEngine() { }

        public void Execute()
        {
            dataManager = new InstrumentDataManager(ticker, eventsQueue);

            if (backTestType == BackTestType.Continuous)
            {
                for(int i = 0; i < 250; i++)
                {
                    for (int j = 1080; j <= 1200; j += 5)
                    {
                        dataManager.SetTradePeriod(i, j);
                        CreateNewSession();
                    }
                }               
            }
            else if (backTestType == BackTestType.Standard)
            {
                CreateNewSession();
            }

            Logger.GenerateReport("NZBWB");
        }

        private void CreateNewSession(int sessionStartDate = 0,
            int sessionStartTime = 1080)
        {
            eventsQueue.Clear();
            executionManager = new SimulatedExecutionManager(eventsQueue, dataManager);
            portfolioManager = new PortfolioManager(eventsQueue, dataManager, initialEquity);
            strategy = new NetZero(eventsQueue, dataManager, portfolioManager);

            session = new TradingSession(
                eventsQueue,
                dataManager,
                executionManager,
                portfolioManager,
                strategy);

            session.Execute();
        }
    }
}
