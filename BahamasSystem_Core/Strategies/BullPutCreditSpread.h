#pragma once

#include "..\Strategy.h"

class BullPutCreditSpread : public Strategy {
public:
	BullPutCreditSpread(std::queue<TradingEvent*>& eventsQueue,
		std::vector<std::string> tickers) :
		Strategy(eventsQueue, tickers) {

	}

	void CalculateSignal(OptionChainUpdateEvent& event) override {
		auto optionChain = event.OptionChains[15];
		auto option = optionChain->OptionContracts["EW3_01/19/2018_C_2585"];
		auto marketData = option->MarketData();

		if (!invested) {
			TradingEvent* tempEvent = new SignalEvent(option->Id, 1, 1);
			eventsQueue.push(tempEvent);
			invested = true;
		}
	}

private:
	bool invested = false;
};