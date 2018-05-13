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
	void ConsoleLog(std::string message) {
		console->info(message);
	}

	void ExportBacktestResults() {
		console->info("Exporting backtest results...");
		this->ExportPortfolioData();
		this->ExportExecutionData();
		this->ExportContractData();
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

	void ExportContractData() {
		for (auto const& data : ContractMarketData) {
			std::string contract_name = data.first;
			std::replace(contract_name.begin(), contract_name.end(), '/', '-');
			std::string fname = contract_fname + contract_name + ".csv";
			std::ofstream outputFile(fname);
			if (outputFile.is_open())
			{
				outputFile << "timestamp,settle_price" << "\n";
				for (int i = 0; i < data.second.size(); i++) {
					outputFile << data.second[i].EventDateTime << "," <<
						data.second[i].Ask << "\n";
				}
				outputFile.close();
			}
		}
	}

public:
	Logger(Logger const&) = delete;
	void operator=(Logger const&) = delete;
};

#endif