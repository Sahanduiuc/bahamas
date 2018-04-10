#include "stdafx.h"
#include "OptionContract.h"
#include "OptionPriceManager.h"

OptionContract::OptionContract(std::string id, std::string underlyingTicker,
	std::string optionTicker, std::string expirationDate,
	OptionPriceManager& priceManager) :
	Id(id), UnderlyingTicker(underlyingTicker), OptionTicker(optionTicker),
	ExpirationDate(expirationDate), priceManager(priceManager) {

}

OptionContract::~OptionContract(){}

BidAskDataFrame OptionContract::MarketData() {
	return marketData[priceManager.GetCurrentTimeStampString()];
}

void OptionContract::AddMarketData(std::string date, BidAskDataFrame dataFrame) {
	marketData[date] = dataFrame;
}