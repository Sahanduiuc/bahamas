#pragma once

#include "..\Strategy.h"
#include "..\PortfolioManager.h"
#include "..\Structure.h"
#include "..\OptionPriceManager.h"
#include "..\Logger.h"

class NetZero : public Strategy {
public:
	NetZero(std::queue<TradingEvent*>& eventsQueue,
		std::vector<std::string> tickers, PortfolioManager& portfolioManager,
		OptionPriceManager& priceManager) :
		portfolioManager(portfolioManager), priceManager(priceManager),
		Strategy(eventsQueue, tickers) {
	
	}

	void CalculateSignal(OptionChainUpdateEvent& event) override {

		Portfolio& portfolio = portfolioManager.GetPortfolio();

		if (invested) {
			//Close the trade if short leg delta  30 > x > 50
			// or if gain is >= 5% of Reg-T risk
			double delta = priceManager.GetCurrentDataFrame(shortLegId).Delta * -1;
			double profitPerc = (portfolio.GetUnrealisedPnL())/maxRisk * 100;
			if ((delta <= 30 || delta >= 50 || profitPerc >= 10) && delta != 0.0) {
				portfolio.CloseAllPositions();
				invested = false;
			}
		}

		if (!invested) {
			OptionChain* optionChain = GetFurthestDteChain(80, event.OptionChains);

			OptionContract* oc_60d = GetDeltaTargetContract(optionChain, 70.0, 'P');
			OptionContract* oc_40d = GetDeltaTargetContract(optionChain, 40.0, 'P');
			OptionContract* oc_20d = GetDeltaTargetContract(optionChain, 10.0, 'P');

			TradingEvent* order_60d = new SignalEvent(oc_60d->Id, 1, 2, tradeCount);
			TradingEvent* order_40d = new SignalEvent(oc_40d->Id, -1, 4, tradeCount);
			TradingEvent* order_20d = new SignalEvent(oc_20d->Id, 1, 2, tradeCount);

			OptionStructure pcs_structure;
			pcs_structure.Id = "NZ";
			pcs_structure.TargetPositions.push_back(static_cast<SignalEvent*>(order_60d));
			pcs_structure.TargetPositions.push_back(static_cast<SignalEvent*>(order_40d));
			pcs_structure.TargetPositions.push_back(static_cast<SignalEvent*>(order_20d));

			double value = GetStructureValue(pcs_structure, priceManager);
			double delta = GetStructureDelta(pcs_structure, priceManager);
			maxRisk = GetStructureRegTRisk(pcs_structure, priceManager);

			eventsQueue.push(order_60d);
			eventsQueue.push(order_40d);
			eventsQueue.push(order_20d);
			
			invested = true;
			shortLegId = oc_40d->Id;

			tradeCount += 1;
			Logger::instance().ConsoleLog("Trade Risk " + std::to_string(maxRisk));
		}
		

		Logger::instance().ConsoleLog(std::to_string(portfolioManager.GetPortfolioValue()));
	}
private:
	int tradeCount = 0;
	bool invested = false;
	double maxRisk = 0.0;
	std::string shortLegId;
	PortfolioManager& portfolioManager;
	OptionPriceManager& priceManager;
};