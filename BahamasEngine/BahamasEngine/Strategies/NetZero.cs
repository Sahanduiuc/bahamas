using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace BahamasEngine.Strategies
{
    public class NetZero : StrategyBase
    {
        private bool isInvested = false;

        public NetZero(Queue<TradingEvent> eventsQueue, InstrumentDataManager dataManager, 
            PortfolioManager portfolioManager):
            base(eventsQueue ,dataManager, portfolioManager)
        {

        }

        public override void ExecuteStrategy(OptionChainUpdateEvent updateEvent)
        {
            if (!isInvested)
            {
                Console.WriteLine($"     Starting new BWB trade");

                OptionChainSnapshot targetChain = Utilities.GetDteTargetChain(
                    updateEvent.OptionChains, 70);

                OptionContract delta20 = Utilities.GetDeltaTargetContract(targetChain,
                    0.20, 'P', DataManager);
                OptionContract delta40 = Utilities.GetDeltaTargetContract(targetChain,
                    0.40, 'P', DataManager);
                OptionContract delta60 = Utilities.GetDeltaTargetContract(targetChain,
                    0.60, 'P', DataManager);

                OrderEvent order20 = new OrderEvent(delta20.ID, 1, 1);
                OrderEvent order40 = new OrderEvent(delta40.ID, -1, 2);
                OrderEvent order60 = new OrderEvent(delta60.ID, 1, 1);

                Structure bwbStructure = new Structure(DataManager, order20, order40, order60);
                double maxRisk = bwbStructure.GetRegTRisk();
                Console.WriteLine($"        Structure Risk : {maxRisk}");

                //EventsQueue.Enqueue(order20);
                //EventsQueue.Enqueue(order40);
                //EventsQueue.Enqueue(order60);

                //isInvested = true;
            }
            Console.WriteLine($"{DataManager.GetCurrentTradingDate()} Portfolio Value " +
                $"{PortfolioManager.GetPortfolioValue()}");
        }
    }
}
