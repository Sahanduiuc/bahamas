#ifndef LOGGER_H_
#define LOGGER_H_

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "spdlog\spdlog.h"

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

	void ExportPortfolioMetrics(Portfolio& portfolio) {
		std::ofstream outputFile("perf_metrics.txt");
		if (outputFile.is_open())
		{
			for (int i = 0; i < portfolio.historicEquity.size(); i++) {
				outputFile << portfolio.historicEquity[i].Price << "\n";
			}
			outputFile.close();
		}
		else console->error("Unable to open file");
	}

	static Logger& instance()
	{
		static Logger instance;
		return instance;
	}

private:
	std::shared_ptr<spdlog::logger> console;
	Logger() {
		console = spdlog::stdout_color_mt("console");
	}

public:
	Logger(Logger const&) = delete;
	void operator=(Logger const&) = delete;
};

#endif