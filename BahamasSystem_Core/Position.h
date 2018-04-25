#ifndef POSITION_H_
#define POSITION_H_

#include <string>

class Position {
public:
	Position() {}
	Position(int, std::string, int, double, double, double, double);
	void CalculatePositionValue();
	void UpdateMarketValue(double, double);
	void ModifyPosition(int, int, double, double);
	virtual ~Position();

	double UnRealisedPnL() const {
		return unrealisedPnL;
	}
	double RealisedPnL() const {
		return realisedPnL;
	}
	double MarketValue() const {
		return marketValue;
	}
	double CostBasis() const {
		return costBasis;
	}
	int Units() const {
		return totalUnits;
	}

	int action;
	std::string ticker;
	int totalUnits;

private:
	int unitsBought = 0;
	int unitsSold = 0;
	int netUnits = 0;
	double totalBuyValue = 0.0;
	double totalSellValue = 0.0;
	double realisedPnL = 0.0;
	double unrealisedPnL = 0.0;
	double costBasis = 0.0;
	double netValue = 0.0;
	double netValueAfterCommission = 0.0;
	double marketValue = 0.0;
	double avgValue = 0.0;
	double avgBuyValue = 0.0;
	double avgSellValue = 0.0;

	double price;
	double totalCommission;

	inline double sign(double val) {
		if (val >= 0)
			return 1.0;
		else
			return -1.0;
	}
};

#endif