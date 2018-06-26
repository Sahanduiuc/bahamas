using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;

namespace BahamasEngine.Strategies
{
    public class NetZero : StrategyBase
    {    
        private string lastTradingDate = "YYYYMMDD";
        private int portfolioId = 0;
        private List<int> portfolioIds = new List<int>();
        private List<double> tradeRisks = new List<double>();
        private List<string> shortIds = new List<string>();

        public NetZero(Queue<TradingEvent> eventsQueue, InstrumentDataManager dataManager,
            PortfolioManager portfolioManager) :
            base(eventsQueue, dataManager, portfolioManager)
        {

        }

        public override void ExecuteStrategy(OptionChainUpdateEvent updateEvent)
        {
            Console.WriteLine($"Trading TimeStamp   {DataManager.GetCurrentTradingDate()} : {DataManager.TimeStampIndex}");
            Console.WriteLine($"Currently managing {PortfolioManager.Portfolios.Count} portfolios");

            foreach (var portfolio in PortfolioManager.Portfolios.Values.ToList())
            {
                double shortDelta = DataManager.GetCurrentOptionDataFrameAsync(shortIds[portfolio.PortfolioId]).GetAwaiter().GetResult().Delta * -100;
                double profitPerc = (PortfolioManager.Portfolios[portfolio.PortfolioId].UnrealisedPnL) / tradeRisks[portfolio.PortfolioId] * 100.0;

                if ((shortDelta <= 30 || shortDelta >= 50 || profitPerc >= 5) && shortDelta != 0.0)
                {
                    Console.WriteLine($"     Closing Trade with PnL % : {profitPerc}");
                    PortfolioManager.LiquidatePortfolio(portfolio.PortfolioId);
                }
            }

            Console.WriteLine($"     Starting new BWB trade");

            OptionChainSnapshot targetChain = Utilities.GetDteTargetChain(
                updateEvent.OptionChains, 70);

            OptionContract wingBottom = Utilities.GetDeltaTargetContract(targetChain,
                0.20, 'P', DataManager);
            OptionContract wingCenter = Utilities.GetDeltaTargetContract(targetChain,
                0.40, 'P', DataManager);
            OptionContract wingTop = Utilities.GetDeltaTargetContract(targetChain,
                0.60, 'P', DataManager);

            SignalEvent orderBottom = new SignalEvent(wingBottom.ID, 1, 1, portfolioId);
            SignalEvent orderCenter = new SignalEvent(wingCenter.ID, -1, 2, portfolioId);
            SignalEvent orderTop = new SignalEvent(wingTop.ID, 1, 1, portfolioId);

            Structure bwbStructure = new Structure(DataManager, orderBottom, orderCenter, orderTop);
            double structureRisk = bwbStructure.GetRegTRisk();
            Console.WriteLine($"        Structure Risk : {structureRisk}");

            EventsQueue.Enqueue(orderBottom);
            EventsQueue.Enqueue(orderCenter);
            EventsQueue.Enqueue(orderTop);

            shortIds.Add(wingCenter.ID);
            tradeRisks.Add(structureRisk);
            portfolioId++;
            portfolioIds.Add(portfolioId);
            lastTradingDate = DataManager.GetCurrentTradingDate();
        }
    }
}
