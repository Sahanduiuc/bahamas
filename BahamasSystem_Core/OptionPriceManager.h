#ifndef OPTIONPRICEMANAGER_H_
#define OPTIONPRICEMANAGER_H_

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
private:
	std::vector<OptionChain> optionChainData;
	std::map<std::string, double> underlyingPrices;
	std::map<std::string, std::vector<FuturesContractDataFrame>> underlyingData;
	std::map<std::string, OptionContract*> optionContracts;
	std::queue<TradingEvent*>& eventsQueue;
	boost::gregorian::date currentPeriod;
	boost::gregorian::date endPeriod;
	bool eod = false;

	void ImportInstrumentData(std::string);
	void ImportOptionData(std::string);
	void GetNextTradingTimeStamp();

};

#endif 

