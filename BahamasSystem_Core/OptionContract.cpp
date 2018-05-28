#include "stdafx.h"
#include "OptionContract.h"
#include "OptionPriceManager.h"

OptionContract::OptionContract(std::string id, std::string underlyingTicker,
	std::string optionTicker, std::string expirationDate, 
	double strike, char type, std::string chainId, OptionPriceManager& priceManager) :
	Id(id), UnderlyingTicker(underlyingTicker), OptionTicker(optionTicker),
	ExpirationDate(expirationDate), Strike(strike), 
	Type(type), ChainId(chainId), priceManager(priceManager) {

}

OptionDataFrame OptionContract::MarketData() {
	return this->priceManager.GetCurrentDataFrame(Id);
}

OptionContract::~OptionContract(){}