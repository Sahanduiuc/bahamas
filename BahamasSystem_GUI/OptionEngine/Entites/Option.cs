using System;
using System.Collections.Generic;
using System.Linq;

namespace OptionEngine.Entities
{
    public class OptionModel
    {
        public enum OptionTypes { Call, Put }

        public int StrikePrice { get; set; }
        public DateTime ExpirationDate { get; set; }
        public double MarketPrice { get; set; }
        public double Delta { get; set; }
        public double Vega { get; set; }
        public double Theta { get; set; }
        public double Gamma { get; set; }
        public OptionTypes OptionType { get; set; }
    }
}
