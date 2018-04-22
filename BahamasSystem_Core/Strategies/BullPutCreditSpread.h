#pragma once

#include "..\Strategy.h"
#include "..\PortfolioManager.h"

class BullPutCreditSpread : public Strategy {
public:
	BullPutCreditSpread(std::queue<TradingEvent*>& eventsQueue,
		std::vector<std::string> tickers, PortfolioManager& portfolioManager) :
		portfolioManager(portfolioManager), Strategy(eventsQueue, tickers) {
	}

	void CalculateSignal(OptionChainUpdateEvent& event) override {

		if (!invested) {
			OptionChain* optionChain = GetFurthestDteChain(140,event.OptionChains);

			std::vector<OptionContract*> sContracts = 
				GetSpread(optionChain, 1, 250, 'P');

			TradingEvent* order_short = new SignalEvent(sContracts[1]->Id, -1, 1);
			eventsQueue.push(order_short);
			TradingEvent* order_long = new SignalEvent(sContracts[0]->Id, 1, 1);
			eventsQueue.push(order_long);
			
			OptionContract* dContract = GetDeltaTargetContract(optionChain, 25.0, 'P');
			invested = true;
		}

		Portfolio& portfolio = portfolioManager.GetPortfolio();

		std::cout << "Data event" << std::endl;
		for (auto const& x : portfolio.GetInvestedPositions()) {
			std::cout << x.first << " " << x.second.UnRealisedPnL() << std::endl;
		}

		std::cout << portfolioManager.GetPortfolioValue() << std::endl;
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

	OptionChain* GetFurthestDteChain(int maxDte, std::vector<OptionChain*>& optionChains) {
		if (optionChains.size() == 0)
			return nullptr;
		
		OptionChain* targetChain = optionChains[0];
		for (int i = 1; i < optionChains.size(); i++) {
			if (optionChains[i]->Dte < maxDte && optionChains[i]->Dte > targetChain->Dte)
				targetChain = optionChains[i];
		}
		return targetChain->Dte <= maxDte ? targetChain : nullptr;
	}

	OptionContract* GetDeltaTargetContract(OptionChain* optionChain, 
		double delta, char optionType) {
		OptionContract* result = nullptr;
		double min_deltaDiff = DBL_MAX;

		for (int i = 0; i < optionChain->PutStrikes.size(); i++) {
			OptionContract* contract = 
				optionChain->PutStrikeMappings[optionChain->PutStrikes[i]];
			
			double deltaDiff = std::abs((contract->MarketData().Delta*-1.0) - delta);
			if (deltaDiff < min_deltaDiff) {
				min_deltaDiff = deltaDiff;
				result = contract;
			}
		}
		return result;
	}

private:
	bool invested = false;
	PortfolioManager& portfolioManager;
};