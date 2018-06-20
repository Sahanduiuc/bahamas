using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BahamasEngine
{
    public abstract class StrategyBase
    {
        internal InstrumentDataManager DataManager;
        internal StrategyUtilities Utilities;
        internal PortfolioManager PortfolioManager;
        internal Queue<TradingEvent> EventsQueue;

        public StrategyBase(Queue<TradingEvent> eventsQueue, InstrumentDataManager dataManager, 
            PortfolioManager portfolioManager)
        {
            this.EventsQueue = eventsQueue;
            this.PortfolioManager = portfolioManager;
            this.DataManager = dataManager;
            this.Utilities = new StrategyUtilities();
        }

        public virtual void ExecuteStrategy(OptionChainUpdateEvent updateEvent)
        {

        }

        public virtual void ExecuteStructureTrades(Structure structure)
        {
            for(int i = 0; i < structure.Positions.Count; i++)
            {
                EventsQueue.Enqueue(structure.Positions[i]);
            }
        }
    }
}
