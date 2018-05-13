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

#include "DataFrames.h"
#include "OptionContract.h"
#include "TradingEvent.h"
#include "PriceManager.h"
#include "DataImporter.h"
#include "OptionChain.h"

class OptionPriceManager : public PriceManager {
public:
	OptionPriceManager(std::queue<TradingEvent*>&,
		std::string ticker,
		boost::gregorian::date&,
		boost::gregorian::date&);
	~OptionPriceManager() {}

	void StreamNextEvent();
	double GetCurrentPrice(std::string);
	BidAskDataFrame GetCurrentDataFrame(std::string);
	bool EOD();
	std::string GetCurrentTimeStampString();
	//boost::gregorian::date GetCurrentTimeStamp() const;

	std::map<std::string, OptionContract*> OptionContracts;
	std::map<std::string, OptionChain*> OptionChains;
	std::vector<std::string> TradingTimeStamps;
	std::map<std::string, 
		std::map<std::string,FuturesContractDataFrame>> UnderlyingData;

private:
	std::vector<OptionChain*> optionChainData;

	std::queue<TradingEvent*>& eventsQueue;
	boost::gregorian::date currentPeriod;
	boost::gregorian::date endPeriod;
	std::map<uint32_t, OptionContract*> closeMappings;
	int currentPeriodIndex;

	bool eod = false;

	void ImportInstrumentData(std::string);
	void LoadPriceData(boost::iostreams::mapped_file&,size_t,size_t);
	void GetNextTradingTimeStamp();
};

#endif 

