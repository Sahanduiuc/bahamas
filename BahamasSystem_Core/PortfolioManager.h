
#ifndef PORTFOLIOHANDLER_H_
#define PORTFOLIOHANDLER_H_

#include "Portfolio.h"
#include "TradingEvent.h"
#include "OrderSizer.h"
#include "RiskManager.h"

#include <queue>

class PortfolioManager {
public:
	PortfolioManager(double, std::queue<TradingEvent*>&, PriceManager&);
	virtual ~PortfolioManager();

	void UpdatePortfolioValue();
	void UpdatePortfolioRecords();
	void ProcessSignal(SignalEvent&);
	void ProcessFill(FillEvent&);

	Portfolio GetPortfolio() const;
	double GetPortfolioValue() const {
		return portfolio.GetEquityValue();
	}
private:
	double currentBalance;
	Portfolio portfolio;
	OrderSizer orderSizer;
	RiskManager riskManager;
	PriceManager& priceManager;
	std::queue<TradingEvent*>& eventsQueue;
};

#endif