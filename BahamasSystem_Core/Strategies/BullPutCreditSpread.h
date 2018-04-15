#pragma once

#include "..\Strategy.h"

class BullPutCreditSpread : public Strategy {
public:
	BullPutCreditSpread(std::queue<TradingEvent*>& eventsQueue,
		std::vector<std::string> tickers) :
		Strategy(eventsQueue, tickers) {
	}

	void CalculateSignal(OptionChainUpdateEvent& event) override {
		std::string chainId = "CL_07/17/2018";
		OptionChain* optionChain = nullptr;
		for (int i = 0; i < event.OptionChains.size(); i++) {
			if (event.OptionChains[i]->ChainId == chainId) {
				optionChain = event.OptionChains[i];
				break;
			}
		}
		auto option = optionChain->OptionContracts["CL_07/17/2018_P_60"];
		auto marketData = option->MarketData();

		std::cout << marketData.Ask << std::endl;

		if (!invested) {
			TradingEvent* tempEvent = new SignalEvent(option->Id, 1, 1);
			eventsQueue.push(tempEvent);
			invested = true;

			for (auto const& x : optionChain->OptionContracts)
			{
				optionChain->TestContracts.push_back(x.second);
			}
		}

		auto testContract = GetContractWithDelta(optionChain, 10.0, 'P');
	}

	OptionContract* GetContractWithDelta(OptionChain* optionChain, double targetDelta, char optionType) {
		OptionContract* targetContract;
		for (int i = 0; i < optionChain->TestContracts.size(); i++)
		{
			auto mktData = optionChain->TestContracts[i];
		}
		
		return nullptr;
	}

private:
	bool invested = false;
};