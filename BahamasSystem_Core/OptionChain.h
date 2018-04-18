#ifndef OPTIONCHAIN_H_
#define OPTIONCHAIN_H_

#include <unordered_map>
#include <string>

#include "float.h"
#include "OptionContract.h"

struct OptionChain {
	std::string ChainId;
	std::string UnderlyingTicker;
	std::string OptionTicker;
	std::string ExpirationDate;
	int Multiplier;
	int Dte;

	std::vector<OptionContract*> OptionContracts;
	std::unordered_map<std::string, OptionContract*> ContractMappings;

	double MinCallStrike = DBL_MAX, MinPutStrike = DBL_MAX;
	double MaxCallStrike, MaxPutStrike = 0.0;	
	std::vector<double> CallStrikes;
	std::unordered_map<double, OptionContract*> CallStrikeMappings;
	std::vector<double> PutStrikes;
	std::unordered_map<double, OptionContract*> PutStrikeMappings;	
};

#endif
