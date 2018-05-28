#ifndef OPTIONCONTRACT_H_
#define OPTIONCONTRACT_H_

#include <string>
#include <unordered_map>

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
	std::string ChainId;
	double Strike;
	char Type;

	OptionContract(std::string, std::string,std::string, std::string, 
		double strike, char type, std::string, OptionPriceManager&);

	OptionDataFrame MarketData();

	~OptionContract();
private:
	OptionPriceManager& priceManager;
};

#endif