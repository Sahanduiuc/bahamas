#ifndef DATAFRAMES_H_
#define DATAFRAMES_H_

#include <string>
#include <boost/bind.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"

class OptionContract;

struct ExecutionDataFrame {
	std::string EventDateTime;
	std::string Ticker;
	int TradeId;
	int Action;
	int Units;
	OptionContract* Contract;
};

struct PriceDataFrame {
	std::string EventDateTime;
	double Price;
};

struct OHCLVDataFrame {
	std::string Ticker;
	std::string EventDateTime;
	double Open;
	double High;
	double Low;
	double Settle;
};

struct OptionDataFrame {
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
	std::string ExpirationDate;
	double Price;
};

#endif