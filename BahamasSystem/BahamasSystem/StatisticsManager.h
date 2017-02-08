#ifndef STATISTICS_H_
#define STATISTICS_H_

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "TradingEvent.h"
#include "PortfolioHandler.h"

class StatisticsManager {
public:
	static StatisticsManager& getInstance() {
		static StatisticsManager instance;
		return instance;
	}

	void UpdateEquityCurve(PortfolioHandler& portfolioHandler,
		PriceManager& priceManager) {
		std::string metric(priceManager.GetDataFrameTimeStamp());
		metric.append(",").append(std::to_string(portfolioHandler.GetPortfolioValue()));
		equityMetrics.push_back(metric);
	}

	void UpdateTradeHistory(FillEvent& event) {
		tradeCount++;
		//TODO:: Add commission
	}

	void UpdatePositionHistory(Position& position) {
		if (position.Units() == 0) {
			positionsExecuted++;

			if (position.RealisedPnL() > 0) 
				profitablePositionCount++;
				
			strategyAccuracy = ( (profitablePositionCount) / ((double)positionsExecuted) ) * 100.0;
		}
	}

	void GenerateTearSheetData() {
		std::ofstream outputFile("perf_metrics.txt");
		if (outputFile.is_open())
		{
			for (auto metric : equityMetrics) {
				outputFile << metric << "\n";
			}

			outputFile.close();
		}
		else std::cout << "Unable to open file" << std::endl;
	}

	//Public Properties
	double GetStrategyAccuracy() const {
		return strategyAccuracy;
	}
	double GetTradeCount() const {
		return tradeCount;
	}
	double GetSharpeRatio() const {

	}
	double GetMaxDrawdown() const {

	}

private:
	StatisticsManager() {}

	int tradeCount = 0;
	int positionsExecuted = 0;
	int profitablePositionCount = 0;
	double strategyAccuracy = 0.0;
	double commissionsVal = 0.0;
	std::vector<std::string> equityMetrics;

public:
	StatisticsManager(StatisticsManager const&) = delete;
	void operator=(StatisticsManager const&) = delete;
};

#endif
