using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BahamasEngine
{
    public enum EventType
    {
        BaseEventType,
        OrderBookUpdateEventType,
        BarEventType,
        SignalEventType,
        OrderEventType,
        FillEventType,
        OptionChainUpdateEventType
    };    

    public abstract class TradingEvent
    {
        public string Ticker { get; private set; }
        public EventType Type { get; private set; }

        public TradingEvent(string ticker, EventType type)
        {
            this.Ticker = ticker;
            this.Type = type;
        }
    }

    public sealed class SignalEvent : TradingEvent
    {
        public int Action { get; private set; }
        public int OrderUnits { get; private set; }

        public SignalEvent(string ticker, int action, int orderUnits)
            : base(ticker,EventType.SignalEventType)
        {
            this.Action = action;
            this.OrderUnits = orderUnits;
        }
    }

    public sealed class OrderEvent : TradingEvent
    {
        public int Action { get; private set; }
        public int OrderUnits { get; private set; }

        public OrderEvent(string ticker, int action, int orderUnits)
            : base(ticker,EventType.OrderEventType)
        {
            this.Action = action;
            this.OrderUnits = orderUnits;
        }
    }

    public sealed class FillEvent : TradingEvent
    {
        public int Action { get; private set; }
        public int OrderUnits { get; private set; }
        public double FillPrice { get; private set; }
        public double Commission { get; private set; }

        public FillEvent(string ticker, int action, int orderUnits,
            double fillPrice, double commission)
            : base(ticker,EventType.FillEventType)
        {
            this.Action = action;
            this.OrderUnits = orderUnits;
            this.FillPrice = fillPrice;
            this.Commission = commission;
        }
    }

    public sealed class OptionChainUpdateEvent : TradingEvent
    {
        public IList<OptionChainSnapshot> OptionChains;

        public OptionChainUpdateEvent(string underlyingTicker)
            : base(underlyingTicker, EventType.OptionChainUpdateEventType)
        {
            OptionChains = new List<OptionChainSnapshot>();
        }
    }

}
