using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BahamasEngine
{
    public class OptionContract
    {
        public string ID { get; private set; }
        public string UnderlyingTicker { get; private set; }
        public string OptionTicker { get; private set; }
        public string ExpirationDate { get; private set; }
        public double Strike { get; private set; }
        public char Type { get; private set; }
        public string ChainId { get; private set; }

        private InstrumentDataManager priceManager;

        public OptionContract(string id, string underlyingTicker, string optionTicker,
            string expirationDate, double strike, char type, string chainId,
            InstrumentDataManager priceManager)
        {
            this.ID = id;
            this.UnderlyingTicker = underlyingTicker;
            this.OptionTicker = optionTicker;
            this.ExpirationDate = expirationDate;
            this.Strike = strike;
            this.Type = type;
            this.ChainId = chainId;
            this.priceManager = priceManager;
        }
    }
}
