using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BahamasEngine
{
    public class PortfolioManager
    {
        private double currentBalance = 0.0;
        private InstrumentDataManager dataManager;
        private Queue<TradingEvent> eventsQueue;
        private OrderSizer orderSizer;
        private RiskManager riskManager;

        public Portfolio Portfolio { get; private set; }

        public PortfolioManager(Queue<TradingEvent> eventsQueue, InstrumentDataManager dataManager,
            double initialBalance)
        {
            this.eventsQueue = eventsQueue;
            this.currentBalance = initialBalance;
            this.dataManager = dataManager;

            this.orderSizer = new OrderSizer();
            this.riskManager = new RiskManager();
            this.Portfolio = new Portfolio(0, eventsQueue, initialBalance, dataManager);
        }

        public void UpdatePortfolioValue()
        {
            this.Portfolio.UpdatePortfolio();
        }

        public double GetPortfolioValue()
        {
            return Portfolio.EquityValue;
        }

        public void ProcessSignal(SignalEvent sEvent)
        {
            MarketOrder order = new MarketOrder
            {
                Ticker = sEvent.Ticker,
                Action = sEvent.Action,
                Units = sEvent.OrderUnits,
                Price = dataManager.GetCurrentPrice(sEvent.Ticker)
            };
            orderSizer.SizeOrder(order, Portfolio);
            IList<MarketOrder> profiledOrders = riskManager.ProfileOrder(order);

            //Place Order on Events queue for execution
            foreach (MarketOrder curOrder in profiledOrders)
            {
                OrderEvent oEvent = new OrderEvent(curOrder.Ticker,
                    curOrder.Action,
                    curOrder.Units);

                eventsQueue.Enqueue(oEvent);
            }
        }

        public void ProcessFill(FillEvent fEvent)
        {
            Portfolio.ProcessPosition(
                fEvent.Ticker,
                fEvent.Action,
                fEvent.FillPrice,
                fEvent.OrderUnits,
                fEvent.Commission);
        }
    }
}
