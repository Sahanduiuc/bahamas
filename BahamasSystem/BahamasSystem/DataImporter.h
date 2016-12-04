#include <vector>
#include <sstream>
#include <istream>
#include <fstream>
#include <functional>
#include <iostream>
#include <boost/coroutine/all.hpp>

class CSVImporter{
public:
	/*
	void ImportCSVData(boost::coroutines::asymmetric_coroutine<std::vector<std::string> >::push_type &sink){
		std::ifstream dataStream("msft.csv");
		if (dataStream.fail()) {
			std::cout << "Error importing data file" << std::endl; return; }

		if(dataStream.good())
			csv_read_row(dataStream, ',');

		while(dataStream.good()){
	    	std::vector<std::string> dataItems = csv_read_row(dataStream, ',');
	    	sink(dataItems);
		}
		dataStream.close();
	}
	*/

	void GetDataItem(std::vector<std::string>& dataRow){
		if(dataStream.is_open()){
			if(dataStream.good()){
				dataRow =  csv_read_row(dataStream, ',');
			}else
				dataRow.clear();
		}else{
			dataStream.open("dis.csv");

			if (dataStream.fail()) {
				std::cout << "Error importing data file" << std::endl; return; }

			dataRow = csv_read_row(dataStream, ',');
		}
	}
private:
	std::ifstream dataStream;

	std::vector<std::string> csv_read_row(std::istream &in, char delimiter)
	{
	    std::stringstream ss;
	    bool inquotes = false;
	    std::vector<std::string> row;//relying on RVO
	    while(in.good())
	    {
	        char c = in.get();
	        if (!inquotes && c=='"') //beginquotechar
	        {
	            inquotes=true;
	        }
	        else if (inquotes && c=='"') //quotechar
	        {
	            if ( in.peek() == '"')//2 consecutive quotes resolve to 1
	            {
	                ss << (char)in.get();
	            }
	            else //endquotechar
	            {
	                inquotes=false;
	            }
	        }
	        else if (!inquotes && c==delimiter) //end of field
	        {
	            row.push_back( ss.str() );
	            ss.str("");
	        }
	        else if (!inquotes && (c=='\r' || c=='\n') )
	        {
	            if(in.peek()=='\n') { in.get(); }
	            row.push_back( ss.str() );
	            return row;
	        }
	        else
	        {
	            ss << c;
	        }
	    }
	}
	std::vector<std::string> csv_read_row(std::string &line, char delimiter)
	{
	    std::stringstream ss(line);
	    return csv_read_row(ss, delimiter);
	}
};
