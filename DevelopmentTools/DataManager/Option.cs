using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataManager
{
    public class MatrixInstance
    {
        public Dictionary<DateTime, List<OptionModel>> Data = new Dictionary<DateTime, List<OptionModel>>();
    }

    public class OptionModel
    {
        public enum OptionTypes { Call, Put }

        public double StrikePrice { get; set; }
        public DateTime ExpirationDate { get; set; }
        public double MarketPrice { get; set; }
        public double Delta { get; set; }
        public double Theta { get; set; }
        public double Vega { get; set; }
        public double Gamma { get; set; }
        public OptionTypes OptionType { get; set; }
    }

    class Option
    {
    }
}
