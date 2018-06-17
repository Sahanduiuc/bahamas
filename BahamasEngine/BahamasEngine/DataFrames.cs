using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BahamasEngine
{
    struct ExecutionDataFrame
    {
        string EventDateTime;
        string Ticker;
        int TradeId;
        int Action;
        int Units;
        OptionContract Contract;
    }

    public struct OptionDataFrame
    {
        public string Ticker;
        public string EventDate;
        public double Bid;
        public int BidSize;
        public double Ask;
        public int Asksize;
        public double Delta;
    }

    struct FuturesDataFrame
    {
        string Ticker;
        string EventDateTime;
        string ContractSymbol;
        string ExpirationDate;
        double Price;
    }

    public struct OHLCVDataFrame
    {
        public string Ticker;
        public string Date;
        public int TimeIndex;
        public double Open;
        public double High;
        public double Low;
        public double Close;
        public int Volume;
    }
}
