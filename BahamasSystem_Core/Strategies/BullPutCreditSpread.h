#pragma once

#include "..\Strategy.h"

class BullPutCreditSpread : public Strategy {
public:
	BullPutCreditSpread(std::queue<TradingEvent*>& eventsQueue,
		std::vector<std::string> tickers) :
		Strategy(eventsQueue, tickers) {
	}

	void CalculateSignal(OptionChainUpdateEvent& event) override {
		std::string chainId = "EW3_01/19/2018";
		OptionChain* optionChain = nullptr;
		for (int i = 0; i < event.OptionChains.size(); i++) {
			if (event.OptionChains[i]->ChainId == chainId) {
				optionChain = event.OptionChains[i];
				break;
			}
		}
		auto option = optionChain->OptionContracts["EW3_01/19/2018_C_2585"];
		auto marketData = option->MarketData();

		if (!invested) {
			TradingEvent* tempEvent = new SignalEvent(option->Id, 1, 1);
			eventsQueue.push(tempEvent);
			invested = true;
		}

		auto testContract = GetContractWithDelta(optionChain, 10.0, 'P');
	}

	OptionContract* GetContractWithDelta(OptionChain* optionChain, double targetDelta, char optionType) {
		OptionContract* targetContract;
		for (auto const& x : optionChain->OptionContracts)
		{
			auto mktData = x.second->MarketData();
		}
		
		return nullptr;
	}

private:
	bool invested = false;
};