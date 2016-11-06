/*
 * OHLCVDataParser.h
 *
 *  Created on: 23 Oct 2016
 *      Author: shamitha
 */

#ifndef OHLCVDATAPARSER_H_
#define OHLCVDATAPARSER_H_

#include <boost/bind.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"

#include "DataImporter.h"

struct OHCLVDataFrame{
	boost::gregorian::date EventDateTime;
	double AdjPrice;
};

class OHLCVDataParser {
public:
	std::map<std::string,std::vector<OHCLVDataFrame> > InstrumentData;

	OHLCVDataParser();
	~OHLCVDataParser();

	void ImportInstrumentData(std::string);
};

#endif /* DATAHANDLERS_OHLCVDATAPARSER_H_ */
