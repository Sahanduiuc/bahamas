#ifndef DATAFRAMES_H_
#define DATAFRAMES_H_

#include <string>
#include <boost/bind.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"

struct PriceDataFrame {
	std::string EventDateTime;
	double Price;
};

struct OHCLVDataFrame {
	std::string Ticker;
	boost::gregorian::date EventDateTime;
	double Open;
	double High;
	double Low;
	double Settle;
};

struct BidAskDataFrame {
	std::string Ticker;
	std::string EventDateTime;
	double Bid;
	double BidSize;
	double Ask;
	double Asksize;
	double Delta;
};

struct FuturesContractDataFrame {
	std::string Ticker;
	std::string EventDateTime;
	std::string ContractSymbol;
	double Price;
};

#endif