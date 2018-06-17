using System;

namespace BahamasEngine
{
    public class OptionPricingHelper
    {
        public OptionPricingHelper() { }

        public double CallPrice(double underlying, double strike,
            double rate, double volatility, double dte)
        {
            return underlying * NormCDF(d_j(1, underlying, strike, rate, volatility, dte)) - strike * Math.Exp(-rate * dte) *
                NormCDF(d_j(2, underlying, strike, rate, volatility, dte));
        }

        public double CallDelta(double underlying, double strike,
            double rate, double volatility, double dte)
        {
            return NormCDF(d_j(1, underlying, strike, rate, volatility, dte));
        }

        public double PutPrice(double underlying, double strike,
            double rate, double volatility, double dte)
        {
            return -underlying * NormCDF(-d_j(1, underlying, strike, rate, volatility, dte)) + strike * Math.Exp(-rate * dte) *
                NormCDF(-d_j(2, underlying, strike, rate, volatility, dte));
        }

        public double PutDelta(double underlying, double strike,
            double rate, double volatility, double dte)
        {
            return NormCDF(d_j(1, underlying, strike, rate, volatility, dte)) - 1;
        }

        public double ImpliedVolatility(char type, double underlying,
                    double strike, double rate, double dte, double optionprice)
        {
            double high = 500.0;
            double low = 0.0;
            double mid = 0.0;

            for (int i = 0; i < 1000; i++)
            {
                mid = (high + low) / 2;
                if (mid < 0.00001)

                    mid = 0.00001;

                double estimate = 0.0;
                if (type == 'C')
                    estimate = CallPrice(underlying, strike, rate, mid, dte);
                else if (type == 'P')
                    estimate = PutPrice(underlying, strike, rate, mid, dte);

                if (estimate > optionprice)
                    high = mid;
                else if (estimate <= optionprice)
                    low = mid;
            }

            return mid;
        }

        #region Private Methods

        double NormPDF(double val)
        {
            return (1.0 / (Math.Pow(2 * Math.PI, 0.5))) * Math.Exp(-0.5 * val * val);
        }

        double NormCDF(double val)
        {
            double k = 1.0 / (1.0 + 0.2316419 * val);
            double k_sum = k * (0.319381530 + k * (-0.356563782 + k * (1.781477937 + k * (-1.821255978 + 1.330274429 * k))));

            if (val >= 0.0)
            {
                return (1.0 - (1.0 / (Math.Pow(2 * Math.PI, 0.5))) * Math.Exp(-0.5 * val * val) * k_sum);
            }
            else
            {
                return 1.0 - NormCDF(-val);
            }
        }

        double d_j(int j, double S, double K, double r, double v, double T)
        {
            return (Math.Log(S / K) + (r + (Math.Pow(-1, j - 1)) * 0.5 * v * v) * T) /
                (v * (Math.Pow(T, 0.5)));
        }

        #endregion
    }
}
