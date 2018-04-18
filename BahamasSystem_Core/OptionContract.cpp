#include "stdafx.h"
#include "OptionContract.h"
#include "OptionPriceManager.h"

OptionContract::OptionContract(std::string id, std::string underlyingTicker,
	std::string optionTicker, std::string expirationDate, 
	double strike, char type, OptionPriceManager& priceManager) :
	Id(id), UnderlyingTicker(underlyingTicker), OptionTicker(optionTicker),
	ExpirationDate(expirationDate), Strike(strike), Type(type), priceManager(priceManager) {

}

OptionContract::~OptionContract(){}

BidAskDataFrame OptionContract::MarketData() {
	return marketData[priceManager.GetCurrentTimeStampString()];
}

void OptionContract::AddMarketData(std::string date, BidAskDataFrame dataFrame) {
	marketData[date] = dataFrame;
}