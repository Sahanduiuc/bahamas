#pragma once

#include "..\Strategy.h"
#include "..\PortfolioManager.h"
#include "..\Structure.h"
#include "..\OptionPriceManager.h"

class BullPutCreditSpread : public Strategy {
public:
	BullPutCreditSpread(std::queue<TradingEvent*>& eventsQueue,
		std::vector<std::string> tickers, PortfolioManager& portfolioManager,
		OptionPriceManager& priceManager):
		portfolioManager(portfolioManager), priceManager(priceManager), 
		Strategy(eventsQueue, tickers) {
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

			invested = true;
		}

		Portfolio& portfolio = portfolioManager.GetPortfolio();

		std::cout << "Data event" << std::endl;
		for (auto const& x : portfolio.GetInvestedPositions()) {
			std::cout << x.first << " " << x.second.UnRealisedPnL() << std::endl;
		}

		std::cout << portfolioManager.GetPortfolioValue() << std::endl;
	}

private:
	bool invested = false;
	PortfolioManager& portfolioManager;
	OptionPriceManager& priceManager;
};