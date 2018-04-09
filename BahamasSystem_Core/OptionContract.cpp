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
	return marketData["09/21/2017"];
}

void OptionContract::AddMarketData(std::string date, BidAskDataFrame dataFrame) {
	marketData[date] = dataFrame;
}