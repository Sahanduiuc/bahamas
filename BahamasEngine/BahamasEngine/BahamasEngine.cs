using BahamasEngine.Strategies;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace BahamasEngine
{
    public class BahamasEngine
    {
        private enum BackTestType
        {
            Continuous,
            Standard
        };

        private const string ticker = "SPX";
        private const double initialEquity = 100000.0;
        private BackTestType backTestType = BackTestType.Continuous;

        public BahamasEngine() { }

        public void Execute()
        {
            MetaDataManager.ImportMetaData(ticker);
            List<Task> sessions = new List<Task>();

            if (backTestType == BackTestType.Continuous)
            {
                for(int i = 0; i < 10; i++)
                {
                    for (int j = Settings.TimeStartIndex; j <= Settings.TimeEndIndex; j += Settings.TimeStepSize)
                    {
                        int iTemp = i;
                        int jTemp = j;
                        Task task =  Task.Run(()=>CreateNewSession(iTemp,jTemp));
                        sessions.Add(task);
                    }
                }               
            }
            else if (backTestType == BackTestType.Standard)
            {
                CreateNewSession(0, Settings.TimeStartIndex);
            }

            Task.WaitAll(sessions.ToArray());
            //Logger.GenerateReport("NZBWB");
        }

        private void CreateNewSession(int sessionStartDate, int sessionStartTime)
        {
            Queue<TradingEvent> eventsQueue = new Queue<TradingEvent>();
            InstrumentDataManager dataManager = new InstrumentDataManager(ticker, eventsQueue, 
                sessionStartDate, sessionStartTime);
            ExecutionManager executionManager = new SimulatedExecutionManager(eventsQueue, dataManager);
            PortfolioManager portfolioManager = new PortfolioManager(eventsQueue, dataManager, initialEquity);
            StrategyBase strategy = new NetZero(eventsQueue, dataManager, portfolioManager);

            TradingSession session = new TradingSession(
                eventsQueue,
                dataManager,
                executionManager,
                portfolioManager,
                strategy);

            session.Execute();
        }
    }
}
