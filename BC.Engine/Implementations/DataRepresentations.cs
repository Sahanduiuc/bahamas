using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace BC.Engine.Implementations
{
    public struct SimplePriceCoordinate
    {
        public long date;
        public string value;
    }

    public class OptionModel
    {
        public enum OptionType { Call, Put };

        public string Instrument;
        public DateTime ExpirationDate;
        public double StrikePrice;
        public OptionType Type;

        public OptionModel(string instrument, DateTime expirationDate,
            double strikePrice, OptionType type)
        {
            this.Instrument = instrument;
            this.ExpirationDate = expirationDate;
            this.StrikePrice = strikePrice;
            this.Type = type;
        }

        public override bool Equals(object obj)
        {
            var targetOption = (OptionModel)obj;
            return (this.Instrument == targetOption.Instrument &&
                    this.ExpirationDate == targetOption.ExpirationDate &&
                    this.StrikePrice == targetOption.StrikePrice &&
                    this.Type == targetOption.Type);
        }

        public override int GetHashCode()
        {
            return (this.Instrument.GetHashCode() +
                this.ExpirationDate.GetHashCode() +
                this.StrikePrice.GetHashCode() +
                this.Type.GetHashCode());
        }
    }
}
