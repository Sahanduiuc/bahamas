#ifndef OPTIONPRICER_H_
#define OPTIONPRICER_H_

#define _USE_MATH_DEFINES

#include <cmath>
#include <math.h>
#include <algorithm>

class OptionPricer {
public:
	static OptionPricer& instance() {
		static OptionPricer instance;
		return instance;
	}

	double CallPrice(const double underlying, const double strike, 
		const double rate, const double volatility, const double dte) {
		return underlying * NormCDF(d_j(1, underlying, strike, rate, volatility, dte)) - strike*exp(-rate*dte) * NormCDF(d_j(2, underlying, strike, rate, volatility, dte));
	}

	double CallDelta(const double underlying, const double strike, 
		const double rate, const double volatility, const double dte) {
		return NormCDF(d_j(1, underlying, strike, rate, volatility, dte));
	}

	double PutPrice(const double underlying, const double strike, 
		const double rate, const double volatility, const double dte) {
		return -underlying*NormCDF(-d_j(1, underlying, strike, rate, volatility, dte)) + strike*exp(-rate*dte) * 
			NormCDF(-d_j(2, underlying, strike, rate, volatility, dte));
	}

	double PutDelta(const double underlying, const double strike, 
		const double rate, const double volatility, const double dte) {
		return NormCDF(d_j(1, underlying, strike, rate, volatility, dte)) - 1;
	}

	double ImpliedVolatility(const char type, const double underlying,
		const double strike, const double rate, 
		const double dte, const double optionprice) {

		double high = 500.0;
		double low = 0.0;
		double mid = 0.0;

		for (int i = 0; i < 10000; i++) {
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
private:
	OptionPricer() {}

	double NormPDF(const double val) {
		return (1.0 / (pow(2 * M_PI, 0.5)))*exp(-0.5*val*val);
	}

	double NormCDF(const double val) {
		double k = 1.0 / (1.0 + 0.2316419*val);
		double k_sum = k*(0.319381530 + k*(-0.356563782 + k*(1.781477937 + k*(-1.821255978 + 1.330274429*k))));

		if (val >= 0.0) {
			return (1.0 - (1.0 / (pow(2 * M_PI, 0.5)))*exp(-0.5*val*val) * k_sum);
		}
		else {
			return 1.0 - NormCDF(-val);
		}
	}

	double d_j(const int j, const double S, const double K, const double r, const double v, const double T) {
		return (log(S / K) + (r + (pow(-1, j - 1))*0.5*v*v)*T) / (v*(pow(T, 0.5)));
	}
public:
	OptionPricer(OptionPricer const&) = delete;
	void operator=(OptionPricer const&) = delete;
};

#endif 

