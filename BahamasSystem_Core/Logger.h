#ifndef LOGGER_H_
#define LOGGER_H_

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
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
	void LogInfo(std::string message) {
		console->info(message);
	}

	void LogError(std::string message){
		console->error(message);
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

	void AddToTimeSeries(std::string series, std::string eventperiod,
		double value) {
		PriceDataFrame dataframe{
			eventperiod,
			value
		};
		TimeSeriesData[series].push_back(dataframe);
	}

	std::vector<PriceDataFrame> PortfolioData;
	std::vector<ExecutionDataFrame> ExecutionData;
	std::map<std::string, std::vector<PriceDataFrame>> TimeSeriesData;

private:
	const std::string portfolio_fname = "portfolio_records.csv";
	const std::string execution_fname = "execution_records.csv";
	const std::string contract_fname = ".\\contract_data\\";

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
			outputFile << "trade_id,timestamp,action,units,option_contract,expiration_date,type,strike" << "\n";
			for (int i = 0; i < PortfolioData.size(); i++) {
				outputFile << ExecutionData[i].TradeId << "," <<
					ExecutionData[i].EventDateTime << "," <<
					ExecutionData[i].Action << "," <<
					ExecutionData[i].Units << "," <<
					ExecutionData[i].Ticker << "," <<
					ExecutionData[i].Contract->ExpirationDate << "," <<
					ExecutionData[i].Contract->Type << "," << 
					ExecutionData[i].Contract->Strike << "\n";
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