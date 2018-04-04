#ifndef OPTIONCHAIN_H_
#define OPTIONCHAIN_H_

#include "OptionContract.h"

class OptionChain {
public:
	std::string UnderlyingTicker;
	std::string OptionTicker;
	std::string ExpirationDate;
	std::vector<double> Strikes;
	std::map<std::string, std::shared_ptr<OptionContract>> OptionContracts;
};

#endif
