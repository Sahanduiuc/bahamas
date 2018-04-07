#ifndef OPTIONCONTRACT_H_
#define OPTIONCONTRACT_H_

#include <string>

#include "DataFrames.h"
#include <boost/bind.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"

class OptionContract {
public:
	std::string ID;
	std::string UnderlyingTicker;
	std::string OptionTicker;
	std::string expirationDate;
	std::map<std::string, BidAskDataFrame> PriceData;

	bool operator <(const OptionContract& rhs) const
	{
		return ID < rhs.ID;
	}
private:

};

#endif