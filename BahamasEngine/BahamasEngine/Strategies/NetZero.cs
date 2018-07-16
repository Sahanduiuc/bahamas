using System;
using System.Collections.Generic;

namespace BahamasEngine.Strategies
{
    public class NetZero : StrategyBase
    {
        private string lastTradingDate = "YYYYMMDD";
        private int portfolioId = 0;
        private string shortId = "";
        private double structureRisk = 0.0;
        private bool isInvested = false;

        public NetZero(Queue<TradingEvent> eventsQueue, InstrumentDataManager dataManager,
            PortfolioManager portfolioManager) :
            base(eventsQueue, dataManager, portfolioManager)
        {

        }

        public override void ExecuteStrategy(OptionChainUpdateEvent updateEvent)
        {
            string currentDate = DataManager.GetCurrentTradingDate();
            if (currentDate.Equals(lastTradingDate))
                return;

            if (isInvested)
            {
                double shortDelta = DataManager.GetCurrentOptionDataFrameAsync(shortId).GetAwaiter().GetResult().Delta * -100;
                double profitPerc = (PortfolioManager.Portfolio.UnrealisedPnL) / structureRisk * 100.0;

                if ((shortDelta <= 25 || shortDelta >= 55 || profitPerc >= 10) && shortDelta != 0.0)
                {
                    Console.WriteLine($"{currentDate}:{DataManager.TimeStampIndex}     Closing Trade with PnL % : {profitPerc}");
                    PortfolioManager.LiquidatePortfolio();
                    isInvested = false;
                    lastTradingDate = DataManager.GetCurrentTradingDate();
                    TerminationEvent tEvent = new TerminationEvent();
                    EventsQueue.Enqueue(tEvent);
                }
            }
            else if (!isInvested)
            {
                Console.WriteLine($"{currentDate}:{DataManager.TimeStampIndex}     Starting new BWB trade");

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
                structureRisk = bwbStructure.GetRegTRisk();
                Console.WriteLine($"{currentDate}:{DataManager.TimeStampIndex}        Structure Risk : {structureRisk}");

                EventsQueue.Enqueue(orderBottom);
                EventsQueue.Enqueue(orderCenter);
                EventsQueue.Enqueue(orderTop);

                shortId = wingCenter.ID;
                portfolioId++;
                lastTradingDate = DataManager.GetCurrentTradingDate();
                isInvested = true;
                Logger.LogSeriesData("RegTRisk", structureRisk, currentDate, DataManager.TimeStampIndex);
            }
        }
    }
}
