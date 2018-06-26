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

        public Dictionary<int, Portfolio> Portfolios { get; private set; }

        public PortfolioManager(Queue<TradingEvent> eventsQueue, InstrumentDataManager dataManager,
            double initialBalance)
        {
            this.initialBalance = initialBalance;
            this.eventsQueue = eventsQueue;
            this.currentBalance = initialBalance;
            this.dataManager = dataManager;

            this.orderSizer = new OrderSizer();
            this.riskManager = new RiskManager();
            Portfolios = new Dictionary<int, Portfolio>();
        }

        public void UpdatePortfolioValues()
        {
            foreach(var element in Portfolios)
            {
                Task.Run(()=>element.Value.UpdatePortfolio());
            }
        }

        public double GetPortfolioValue(int portfolioId)
        {
            InitializePortfolio(portfolioId);
            return Portfolios[portfolioId].EquityValue;
        }

        public void ProcessSignal(SignalEvent sEvent)
        {
            InitializePortfolio(sEvent.PortfolioId);

            MarketOrder order = new MarketOrder
            {
                Ticker = sEvent.Ticker,
                Action = sEvent.Action,
                Units = sEvent.OrderUnits,
                Price = dataManager.GetCurrentPrice(sEvent.Ticker)
            };
            orderSizer.SizeOrder(order, Portfolios[sEvent.PortfolioId]);
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
            Portfolios[fEvent.PortfolioId].ProcessPosition(
                fEvent.Ticker,
                fEvent.Action,
                fEvent.FillPrice,
                fEvent.OrderUnits,
                fEvent.Commission);
        }

        public void LiquidatePortfolio(int portfolioId)
        {
            Portfolios[portfolioId].CloseAllPositions();
            Portfolios.Remove(portfolioId);
        }

        private void InitializePortfolio(int portfolioId)
        {
            if (!Portfolios.ContainsKey(portfolioId))
                Portfolios[portfolioId] = new Portfolio(portfolioId, eventsQueue,
                    initialBalance, dataManager);
        }
    }
}
