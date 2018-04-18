#ifndef OPTIONCONTRACT_H_
#define OPTIONCONTRACT_H_

#include <string>

#include "DataFrames.h"
#include <boost/bind.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"

class OptionPriceManager;
class OptionContract {
public:
	std::string Id;
	std::string UnderlyingTicker;
	std::string OptionTicker;
	std::string ExpirationDate;
	double Strike;
	char Type;

	OptionContract(std::string, std::string,std::string, std::string, 
		double strike, char type, OptionPriceManager&);

	~OptionContract();

	BidAskDataFrame MarketData();

	void AddMarketData(std::string, BidAskDataFrame);
private:
	std::map<std::string, BidAskDataFrame> marketData;
	OptionPriceManager& priceManager;
};

#endif