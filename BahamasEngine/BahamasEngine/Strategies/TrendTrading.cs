using System.Collections.Generic;

namespace BahamasEngine.Strategies
{
    public class TrendTrading : StrategyBase
    {
        public string[] tradeData = null;

        public TrendTrading(Queue<TradingEvent> eventsQueue, InstrumentDataManager dataManager,
            PortfolioManager portfolioManager) :
            base(eventsQueue, dataManager, portfolioManager)
        {

        }

        public override void ExecuteStrategy(OptionChainUpdateEvent updateEvent)
        {

        }
    }
}
