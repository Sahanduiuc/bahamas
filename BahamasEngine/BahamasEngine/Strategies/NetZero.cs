using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace BahamasEngine.Strategies
{
    public class NetZero : StrategyBase
    {
        private bool isInvested = false;
        private string shortContractId = "";
        private double structureRisk = 0.0;
        private string lastTradingDate = "YYYYMMDD";
        private int daysInTrade = 0;

        public NetZero(Queue<TradingEvent> eventsQueue, InstrumentDataManager dataManager, 
            PortfolioManager portfolioManager):
            base(eventsQueue ,dataManager, portfolioManager)
        {

        }

        public override void ExecuteStrategy(OptionChainUpdateEvent updateEvent)
        {
            //if (DataManager.GetCurrentTradingDate() == "20170227")
            //    Console.WriteLine("");

            Console.WriteLine($"Trading TimeStamp   {DataManager.GetCurrentTradingDate()} : {DataManager.TimeStampIndex}");
            Console.WriteLine($"    Portfolio Value {PortfolioManager.GetPortfolioValue()}");

            string currentDate = DataManager.GetCurrentTradingDate();
            if (currentDate.Equals(lastTradingDate))
                return;

            if (isInvested)
            {
                double shortDelta = DataManager.GetCurrentOptionDataFrameAsync(shortContractId).GetAwaiter().GetResult().Delta * -100;
                double profitPerc = (PortfolioManager.Portfolio.UnrealisedPnL)/structureRisk * 100.0;

                if ((shortDelta <= 25 || shortDelta >= 55 || profitPerc >= 10) && shortDelta != 0.0)
                {
                    Console.WriteLine($"     Closing Trade with PnL % : {profitPerc}");
                    PortfolioManager.Portfolio.CloseAllPositions();
                    isInvested = false;

                    daysInTrade = 0;
                    lastTradingDate = DataManager.GetCurrentTradingDate();
                }
            }
            else if (!isInvested)
            {
                Console.WriteLine($"     Starting new BWB trade");

                OptionChainSnapshot targetChain = Utilities.GetDteTargetChain(
                    updateEvent.OptionChains, 70);

                OptionContract wingBottom = Utilities.GetDeltaTargetContract(targetChain,
                    0.10, 'P', DataManager);
                OptionContract wingCenter = Utilities.GetDeltaTargetContract(targetChain,
                    0.40, 'P', DataManager);
                OptionContract wingTop = Utilities.GetDeltaTargetContract(targetChain,
                    0.70, 'P', DataManager);

                OrderEvent orderBottom = new OrderEvent(wingBottom.ID, 1, 1);
                OrderEvent orderCenter = new OrderEvent(wingCenter.ID, -1, 2);
                OrderEvent orderTop = new OrderEvent(wingTop.ID, 1, 1);

                Structure bwbStructure = new Structure(DataManager, orderBottom, orderCenter, orderTop);
                structureRisk = bwbStructure.GetRegTRisk();
                Console.WriteLine($"        Structure Risk : {structureRisk}");

                //EventsQueue.Enqueue(orderBottom);
                //EventsQueue.Enqueue(orderCenter);
                //EventsQueue.Enqueue(orderTop);

                //shortContractId = wingCenter.ID;
                //isInvested = true;

                //daysInTrade = 0;
                //lastTradingDate = DataManager.GetCurrentTradingDate();
            }

        }
    }
}
