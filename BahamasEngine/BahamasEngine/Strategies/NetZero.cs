using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace BahamasEngine.Strategies
{
    public class NetZero : StrategyBase
    {

        private string shortContractId = "";
        private double structureRisk = 0.0;
        private string lastTradingDate = "YYYYMMDD";
        private int portfolioId = 0;
        private List<int> portfolioIds = new List<int>();
        private List<string> shortIds = new List<string>();

        public NetZero(Queue<TradingEvent> eventsQueue, InstrumentDataManager dataManager,
            PortfolioManager portfolioManager) :
            base(eventsQueue, dataManager, portfolioManager)
        {

        }

        public override void ExecuteStrategy(OptionChainUpdateEvent updateEvent)
        {
            //if (DataManager.GetCurrentTradingDate() == "20170227")
            //    Console.WriteLine("");

            Console.WriteLine($"Trading TimeStamp   {DataManager.GetCurrentTradingDate()} : {DataManager.TimeStampIndex}");

            //double shortDelta = DataManager.GetCurrentOptionDataFrameAsync(shortContractId).GetAwaiter().GetResult().Delta * -100;
            //double profitPerc = (PortfolioManager.Portfolios[portfolioId].UnrealisedPnL) / structureRisk * 100.0;

            //if ((shortDelta <= 25 || shortDelta >= 55 || profitPerc >= 10) && shortDelta != 0.0)
            //{
            //    Console.WriteLine($"     Closing Trade with PnL % : {profitPerc}");
            //    PortfolioManager.Portfolios[0].CloseAllPositions();

            //    lastTradingDate = DataManager.GetCurrentTradingDate();
            //}

            Console.WriteLine($"     Starting new BWB trade");

            OptionChainSnapshot targetChain = Utilities.GetDteTargetChain(
                updateEvent.OptionChains, 70);

            OptionContract wingBottom = Utilities.GetDeltaTargetContract(targetChain,
                0.10, 'P', DataManager);
            OptionContract wingCenter = Utilities.GetDeltaTargetContract(targetChain,
                0.40, 'P', DataManager);
            OptionContract wingTop = Utilities.GetDeltaTargetContract(targetChain,
                0.70, 'P', DataManager);

            SignalEvent orderBottom = new SignalEvent(wingBottom.ID, 1, 1, portfolioId);
            SignalEvent orderCenter = new SignalEvent(wingCenter.ID, -1, 2, portfolioId);
            SignalEvent orderTop = new SignalEvent(wingTop.ID, 1, 1, portfolioId);

            Structure bwbStructure = new Structure(DataManager, orderBottom, orderCenter, orderTop);
            structureRisk = bwbStructure.GetRegTRisk();
            Console.WriteLine($"        Structure Risk : {structureRisk}");

            //EventsQueue.Enqueue(orderBottom);
            //EventsQueue.Enqueue(orderCenter);
            //EventsQueue.Enqueue(orderTop);

            shortIds.Add(wingCenter.ID);
            portfolioId++;
            portfolioIds.Add(portfolioId);
            lastTradingDate = DataManager.GetCurrentTradingDate();
        }
    }
}
