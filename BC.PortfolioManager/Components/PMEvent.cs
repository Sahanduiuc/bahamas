using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BC.PortfolioManager
{
    public enum EventType
    {
        TICK,OHLCV,SIGNAL,ORDER,FILL
    }

    public abstract class PMEvent
    {
        public EventType EventType { get; set; }
    }

    public class OHLCVEvent: PMEvent
    {

    }

    public class OrderEvent: PMEvent
    {

    }

    public class SignalEvent: PMEvent
    {

    }
}
