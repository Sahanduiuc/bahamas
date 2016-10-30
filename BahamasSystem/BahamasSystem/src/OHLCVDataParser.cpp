/*
 * OHLCVDataParser.cpp
 *
 *  Created on: 23 Oct 2016
 *      Author: shamitha
 */

#include "OHLCVDataParser.h"

OHLCVDataParser::OHLCVDataParser() {

	/*
	CSVImporter test;
    boost::coroutines::asymmetric_coroutine<std::vector<std::string> >::pull_type coro
    {
        boost::bind(&CSVImporter::ImportCSVData, &test, _1)
    };
*/

}

OHLCVDataParser::~OHLCVDataParser() {

}

void OHLCVDataParser::ImportInstrumentData(std::string ticker){

	CSVImporter csvImporter;
	std::vector<std::string> dataRow;
	std::vector<OHCLVDataFrame> priceData;

	//Skip header row
	csvImporter.GetDataItem(dataRow);

	csvImporter.GetDataItem(dataRow);
	while(!dataRow.empty()){
		boost::gregorian::date eventDate = boost::gregorian::from_string(dataRow[0]);

		priceData.push_back(OHCLVDataFrame{
			eventDate,
			atof(dataRow[6].c_str())
		});
		csvImporter.GetDataItem(dataRow);
	}
	InstrumentData[ticker] = priceData;
}

