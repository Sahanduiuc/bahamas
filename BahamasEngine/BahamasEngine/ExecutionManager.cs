using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BahamasEngine
{
    public abstract class ExecutionManager
    {
        internal Queue<TradingEvent> eventsQueue;
        internal InstrumentDataManager dataManager;

        public ExecutionManager(Queue<TradingEvent> eventsQueue, InstrumentDataManager dataManager)
        {
            this.eventsQueue = eventsQueue;
            this.dataManager = dataManager;
        }

        public virtual void ExecuteOrder(OrderEvent orderEvent) { }
    }

    public class SimulatedExecutionManager : ExecutionManager
    {
        public SimulatedExecutionManager(Queue<TradingEvent> eventsQueue, InstrumentDataManager dataManager)
            : base(eventsQueue, dataManager)
        {
        }

        public override void ExecuteOrder(OrderEvent orderEvent)
        {
            double commission = GetCommission(orderEvent);

            FillEvent tempEvent = new FillEvent(
                orderEvent.Ticker,
                orderEvent.Action,
                orderEvent.OrderUnits,
                dataManager.GetCurrentPrice(orderEvent.Ticker),
                commission,
                orderEvent.PortfolioId);

            eventsQueue.Enqueue(tempEvent);
        }

        private double GetCommission(OrderEvent orderEvent)
        {
            return orderEvent.OrderUnits * 2.35;
        }
    }

}
