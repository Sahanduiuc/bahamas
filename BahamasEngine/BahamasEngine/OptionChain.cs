using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BahamasEngine
{
    public class OptionChain
    {
        private DateTime chainExpDate;

        public string ChainId { get; set; }
        public string UnderlyingTicker { get; set; }
        public string OptionTicker { get; set; }
        public string ExpirationDate { get; set; }
        public uint Multiplier { get; set; }

        public OptionChain(string chainId, string underlyingTicker, string optionTicker,
            string expirationDate, uint multiplier)
        {
            ChainId = chainId;
            UnderlyingTicker = underlyingTicker;
            OptionTicker = optionTicker;
            ExpirationDate = expirationDate;
            Multiplier = multiplier;

            chainExpDate = DateTime.ParseExact(expirationDate,
                InstrumentDataManager.DATEFORMAT, CultureInfo.InvariantCulture);
        }

        public int GetDte(InstrumentDataManager dataManager)
        {
            DateTime currentPeriod = DateTime.ParseExact(dataManager.GetCurrentTradingDate(),
                        InstrumentDataManager.DATEFORMAT, CultureInfo.InvariantCulture);
            int dte = (chainExpDate - currentPeriod).Days;
            return dte;
        }
    }

    public class OptionChainSnapshot
    {
        public OptionChain OptionChain { get; set; }

        public List<OptionContract> CallOptionContracts;
        public List<OptionContract> PutOptionContracts;

        public OptionChainSnapshot(OptionChain optionChain)
        {
            this.OptionChain = optionChain;

            this.CallOptionContracts = new List<OptionContract>();
            this.PutOptionContracts = new List<OptionContract>();
        }
    }
}
