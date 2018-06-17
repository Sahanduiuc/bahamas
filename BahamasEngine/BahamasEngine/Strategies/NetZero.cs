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
                OptionChainSnapshot targetChain = Utilities.GetDteTargetChain(
                    updateEvent.OptionChains, 70);


                Stopwatch stopWatch = new Stopwatch();
                stopWatch.Start();

                OptionContract delta20 = Utilities.GetDeltaTargetContract(targetChain,
                    0.20, 'P', DataManager);

                stopWatch.Stop();
                Console.WriteLine("RunTime " + stopWatch.ElapsedMilliseconds);

                //OptionContract delta40 = Utilities.GetDeltaTargetContract(targetChain,
                //    0.40, 'P', DataManager);
                //OptionContract delta60 = Utilities.GetDeltaTargetContract(targetChain,
                //    0.60, 'P', DataManager);

                //OrderEvent order = new OrderEvent(delta20.ID, -1, 1);
                //EventsQueue.Enqueue(order);

                //isInvested = true;
            }
            Console.WriteLine($"{DataManager.GetCurrentTradingDate()} Portfolio Value " +
                $"{PortfolioManager.GetPortfolioValue()}");
        }
    }
}
