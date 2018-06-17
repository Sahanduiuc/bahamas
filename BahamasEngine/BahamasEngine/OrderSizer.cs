using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BahamasEngine
{
    public struct MarketOrder
    {
        public string Ticker;
        public int Action;
        public int Units;
        public double Price;
    }

    public class OrderSizer
    {
        public OrderSizer()
        {

        }

        //Basic Position Sizing
        public void SizeOrder(MarketOrder order, Portfolio portfolio)
        {
            //TODO
            //CURRENT: Allocate each instrument 10% of the equity
            if (order.Units == 0)
            {
                if (order.Action == 1)
                {
                    order.Units = Convert.ToInt32((portfolio.EquityValue * 0.1) / order.Price);
                }
                else if (order.Action == -1)
                {
                    order.Units = portfolio.InvestedPositions[order.Ticker].Units;
                }
            }
        }
    }
}
