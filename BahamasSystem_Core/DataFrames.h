#ifndef DATAFRAMES_H_
#define DATAFRAMES_H_

#include <string>
#include <boost/bind.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"

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
	boost::gregorian::date EventDateTime;
	double Bid;
	double BidSize;
	double Ask;
	double Asksize;
};

#endif