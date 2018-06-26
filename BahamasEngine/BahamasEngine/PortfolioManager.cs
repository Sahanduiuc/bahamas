using System.Collections.Generic;
using System.Threading.Tasks;

namespace BahamasEngine
{
    public class PortfolioManager
    {
        private double currentBalance = 0.0;
        private double initialBalance = 0.0;
        private InstrumentDataManager dataManager;
        private Queue<TradingEvent> eventsQueue;
        private OrderSizer orderSizer;
        private RiskManager riskManager;

        public Portfolio Portfolio;

        public PortfolioManager(Queue<TradingEvent> eventsQueue, InstrumentDataManager dataManager,
            double initialBalance)
        {
            this.initialBalance = initialBalance;
            this.eventsQueue = eventsQueue;
            this.currentBalance = initialBalance;
            this.dataManager = dataManager;

            this.orderSizer = new OrderSizer();
            this.riskManager = new RiskManager();
            Portfolio = new Portfolio(0, eventsQueue, initialBalance, dataManager);
        }

        public void UpdatePortfolioValues()
        {
            Portfolio.UpdatePortfolio();
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
                    curOrder.Units,
                    sEvent.PortfolioId);

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

        public void LiquidatePortfolio()
        {
            Portfolio.CloseAllPositions();
        }
    }
}
