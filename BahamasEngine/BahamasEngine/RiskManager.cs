using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BahamasEngine
{
    public class RiskManager
    {
        public RiskManager()
        {

        }

        public IList<MarketOrder> ProfileOrder(MarketOrder order)
        {
            IList<MarketOrder> orders = new List<MarketOrder> { order };
            return orders;
        }
    }
}
