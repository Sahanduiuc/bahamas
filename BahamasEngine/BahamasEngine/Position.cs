using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BahamasEngine
{
    public class Position
    {
        public readonly string Ticker;
        public int Action { get; private set; }
        public int Units { get; private set; }       
        public double NetCommission { get; private set; }
        public double UnRealisedPnL { get; private set; }
        public double RealisedPnL { get; private set; }
        public double CostBasis { get; private set; }
        public double MarketValue { get; private set; }

        private int unitsBought;
        private int unitsSold;
        private int netUnits;
        private double totalBuyValue;
        private double totalSellValue;                       
        private double netValue;
        private double netValueAfterCommission;        
        private double avgValue;
        private double avgBuyValue;
        private double avgSellValue;
        private double purchasePrice;

        public Position(string ticker, int action, int units,
            double purchasePrice, double commission, double bid, double ask)
        {
            this.Ticker = ticker;
            this.Action = action;
            this.Units = units;
            this.purchasePrice = purchasePrice;
            this.NetCommission = commission;

            CalculatePositionValue();
            UpdateMarketValue(purchasePrice);
        }

        public void CalculatePositionValue()
        {
            if (Action == 1)
            {
                unitsBought = Units;
                avgBuyValue = purchasePrice;
                totalBuyValue = unitsBought * purchasePrice;
                avgValue = ((purchasePrice * Units) + NetCommission) / Units;
                CostBasis = Units * avgValue;
            } else if (Action == -1)
            {
                unitsSold = Units;
                avgSellValue = purchasePrice;
                totalSellValue = unitsSold * purchasePrice;
                avgValue = ((purchasePrice * Units) - NetCommission) / Units;
                CostBasis = (Units * avgValue) * -1.0;
            }
            netUnits = unitsBought - unitsSold;
            netValue = totalSellValue - totalBuyValue;
            netValueAfterCommission = netValue - NetCommission;
        }

        public void UpdateMarketValue(double price)
        {
            double midValue = price;
            MarketValue = Units * midValue * Math.Sign(netUnits);
            UnRealisedPnL = MarketValue - CostBasis;
            RealisedPnL = MarketValue + netValueAfterCommission;
        }

        public void ModifyPosition(int action, int units, double price,
            double commission)
        {
            NetCommission += commission;

            if(action == 1)
            {
                avgBuyValue = ((avgBuyValue * unitsBought) + (price * units)) / (units + unitsBought);
                avgValue = ((avgValue * unitsBought) + (price * units) + commission) / (units + unitsBought);
                unitsBought += units;
                totalBuyValue = unitsBought * avgBuyValue;
            }
            else if (action == -1)
            {
                avgSellValue = ((avgSellValue * unitsSold) + (price * units)) / (units + unitsSold);
                avgValue = ((avgValue * unitsSold) + (price * units) - commission) / (units + unitsSold);
                unitsSold += units;
                totalSellValue = unitsSold * avgSellValue;
            }

            netUnits = unitsBought - unitsSold;
            Units = netUnits;
            netValue = totalSellValue - totalBuyValue;
            netValueAfterCommission = netValue - NetCommission;
            CostBasis = Units * avgValue;
        }

    }
}
