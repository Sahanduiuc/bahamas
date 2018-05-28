#ifndef OPTIONPRICEMANAGER_H_
#define OPTIONPRICEMANAGER_H_

#include <unordered_set>
#include <queue>
#include <boost/bind.hpp>
#include <algorithm> 
#include <cstring>
#include <boost/iostreams/stream.hpp>  
#include <boost/filesystem.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"
#include <boost/date_time/gregorian/gregorian_io.hpp>
#include <boost/iostreams/device/mapped_file.hpp> 
#include <locale>
#include <thread>
#include "sqlite3.h"

#include "DataFrames.h"
#include "OptionContract.h"
#include "TradingEvent.h"
#include "PriceManager.h"
#include "DataImporter.h"
#include "OptionChain.h"
#include "Logger.h"
#include "OptionPricer.h"

class OptionPriceManager : public PriceManager {
public:
	OptionPriceManager(std::queue<TradingEvent*>&,
		std::string ticker,
		boost::gregorian::date&,
		boost::gregorian::date&);
	~OptionPriceManager() {}

	void StreamNextEvent();
	double GetCurrentPrice(std::string);
	OptionDataFrame GetCurrentDataFrame(std::string);
	bool EOD();
	std::string GetCurrentTimeStampString();
	//OHCLVDataFrame GetFuturesDataFrame(std::string);
	//boost::gregorian::date GetCurrentTimeStamp() const;

	std::map<std::string, OptionContract*> OptionContracts;
	std::vector<std::string> TradingDates;
	std::map<std::string, 
		std::map<std::string,FuturesContractDataFrame>> FuturesData;

	std::map<std::string, std::map<std::string,OptionChain*>> OptionChainHistory;
private:
	std::queue<TradingEvent*>& eventsQueue;
	boost::gregorian::date currentPeriod;
	boost::gregorian::date endPeriod;
	int currentDateIndex;
	std::string QuoteTime;

	bool eod = false;

	void ImportInstrumentData(std::string);
	void GetNextTradingTimeStamp();

	void TestMethod();
};

#endif 
