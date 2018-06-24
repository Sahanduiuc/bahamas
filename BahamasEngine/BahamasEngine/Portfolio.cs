using System.Collections.Generic;

namespace BahamasEngine
{
    public class Portfolio
    {
        private double cashBalance = 0.0;
        private double initialBalance = 0.0;
        private double realisedPnL = 0.0;
        private double unrealisedPnL = 0.0;
        private double equity = 0.0;
        private readonly int portfolioId;

        private Queue<TradingEvent> eventsQueue;
        private InstrumentDataManager dataManager;

        public int PortfolioId { get { return portfolioId; }  }
        public double UnrealisedPnL { get { return unrealisedPnL; } }
        public double EquityValue { get { return equity; } }
        public Dictionary<string, Position> InvestedPositions { get; private set; }

        public Portfolio(int portfolioId, Queue<TradingEvent> eventsQueue, double initialBalance, 
            InstrumentDataManager dataManager)
        {
            this.portfolioId = portfolioId;
            this.eventsQueue = eventsQueue;
            this.cashBalance = initialBalance;
            this.initialBalance = initialBalance;
            this.equity = initialBalance;
            this.dataManager = dataManager;

            this.InvestedPositions = new Dictionary<string, Position>();
        }

        public void UpdatePortfolio()
        {
            unrealisedPnL = 0;
            equity = realisedPnL;
            equity += initialBalance;

            foreach(KeyValuePair<string, Position> element in InvestedPositions)
            {
                Position targetPosition = element.Value;

                //TODO: Implement Bid Ask
                double price = dataManager.GetCurrentPrice(element.Key);
                double bid = price;
                double ask = price;

                targetPosition.UpdateMarketValue(price);
                unrealisedPnL += targetPosition.UnRealisedPnL;
                double netPnL = targetPosition.RealisedPnL - targetPosition.UnRealisedPnL;
                equity += targetPosition.MarketValue - targetPosition.CostBasis + netPnL;
            }
        }

        public void ProcessPosition(string ticker, int action, double price,
            int units, double commission)
        {
            if (action == 0)
                return;

            if (action == 1)
                cashBalance -= ((price * units) + commission);
            else if (action == -1)
                cashBalance += ((price * units) - commission);

            if (!InvestedPositions.ContainsKey(ticker))
                AddPosition(ticker, action, units, price, commission);
            else
                UpdatePosition(ticker, action, units, price, commission);
        }

        public void CloseAllPositions()
        {
            foreach(var element in InvestedPositions)
            {
                SignalEvent sEvent = new SignalEvent(element.Key,
                    element.Value.Action * -1, element.Value.Units, 0);
                eventsQueue.Enqueue(sEvent);
            }
        }

        #region Private Methods

        private void AddPosition(string ticker, int action, int units, double price,
            double commission)
        {
            double bid = price;
            double ask = price;

            InvestedPositions[ticker] = new Position(ticker,
                action,
                units,
                price,
                commission,
                bid,
                ask);

            UpdatePortfolio();
        }

        private void UpdatePosition(string ticker, int action, int units, double price,
            double commission)
        {
            InvestedPositions[ticker].ModifyPosition(action, units, price, commission);

            double currentPrice = dataManager.GetCurrentPrice(ticker);
            double bid = currentPrice;
            double ask = currentPrice;

            InvestedPositions[ticker].UpdateMarketValue(currentPrice);

            if (InvestedPositions[ticker].Units == 0)
            {
                realisedPnL += InvestedPositions[ticker].RealisedPnL;
                InvestedPositions.Remove(ticker);
            }

            UpdatePortfolio();
        }

#endregion
    }
}
