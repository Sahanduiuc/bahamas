#ifndef OPTIONCHAIN_H_
#define OPTIONCHAIN_H_

#include "OptionContract.h"

class OptionChain {
public:
	std::string UnderlyingTicker;
	std::string OptionTicker;
	std::string ExpirationDate;
	std::vector<double> Strikes;
	std::map<std::string, OptionContract*> OptionContracts;
	std::vector<OptionContract*> TestContracts;
	std::string ChainId;

	OptionChain(std::string chainId, std::string underlyingTicker, std::string optionTicker,
		std::string expDate) : ChainId(chainId), UnderlyingTicker(underlyingTicker), 
		OptionTicker(optionTicker), ExpirationDate(expDate) {
	}
};

#endif
