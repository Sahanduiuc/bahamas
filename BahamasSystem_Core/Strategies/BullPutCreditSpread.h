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

		if (!invested) {
			std::vector<OptionContract*> sContracts = 
				GetSpread(optionChain, 1, 250, 'P');

			TradingEvent* order_short = new SignalEvent(sContracts[1]->Id, -1, 1);
			eventsQueue.push(order_short);
			TradingEvent* order_long = new SignalEvent(sContracts[0]->Id, 1, 1);
			eventsQueue.push(order_long);
			
			invested = true;
		}
	}

	std::vector<OptionContract*> GetSpread(OptionChain* optionChain, double width,
		double targetValue, char type) {
		std::sort(optionChain->PutStrikes.begin(), optionChain->PutStrikes.end());
		std::vector<OptionContract*> results;

		for (int i = 0; i < optionChain->PutStrikes.size(); i++) {

			double strike_a = optionChain->PutStrikes[i];
			double strike_b = optionChain->PutStrikes[i] + width;

			if (optionChain->PutStrikeMappings.find(strike_b) == 
				optionChain->PutStrikeMappings.end())
				continue;

			OptionContract* contract_a = optionChain->PutStrikeMappings[strike_a];
			OptionContract* contract_b = optionChain->PutStrikeMappings[strike_b];

			if ((std::abs(contract_b->MarketData().Ask - 
				contract_a->MarketData().Ask)) > targetValue) {
				results.push_back(contract_a);
				results.push_back(contract_b);
				break;
			}
		}

		return results;
	}

private:
	bool invested = false;
};