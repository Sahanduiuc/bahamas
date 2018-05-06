#ifndef LOGGER_H_
#define LOGGER_H_

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "spdlog\spdlog.h"
#include "DataFrames.h"

class Portfolio;

enum ConsoleLogType {
	info,
	error,
	warn
};

class Logger {
public:
	void ConsoleLog(std::string message) {
		console->info(message);
	}

	void ExportBacktestResults() {
		console->info("Exporting backtest results...");
		this->ExportPortfolioData();
		this->ExportExecutionData();
		console->info("Export complete.");
	}

	static Logger& instance()
	{
		static Logger instance;
		return instance;
	}

	std::vector<PriceDataFrame> PortfolioData;
	std::vector<ExecutionDataFrame> ExecutionData;
	std::map<std::string, std::vector<BidAskDataFrame>> ContractMarketData;

private:
	const std::string portfolio_fname = "portfolio_records.csv";
	const std::string execution_fname = "execution_records.csv";
	const std::string contract_fname = "\\contract_data\\";

	std::shared_ptr<spdlog::logger> console;
	Logger() {
		console = spdlog::stdout_color_mt("console");
	}

	void ExportPortfolioData() {
		std::ofstream outputFile(portfolio_fname);
		if (outputFile.is_open())
		{
			outputFile << "timestamp,portfolio_equity" << "\n";
			for (int i = 0; i < PortfolioData.size(); i++) {
				outputFile << PortfolioData[i].EventDateTime << "," <<
					PortfolioData[i].Price << "\n";
			}
			outputFile.close();
		}
		else console->error("[ExportPortfolioData] Unable to open file");
	}

	void ExportExecutionData() {
		std::ofstream outputFile(execution_fname);
		if (outputFile.is_open())
		{
			outputFile << "timestamp,option_contract,trade_id" << "\n";
			for (int i = 0; i < PortfolioData.size(); i++) {
				outputFile << ExecutionData[i].TradeId << "," <<
					ExecutionData[i].EventDateTime << "," <<
					ExecutionData[i].Ticker <<"\n";
			}
			outputFile.close();
		}
		else console->error("[ExportExecutionData] Unable to open file");
	}

public:
	Logger(Logger const&) = delete;
	void operator=(Logger const&) = delete;
};

#endif