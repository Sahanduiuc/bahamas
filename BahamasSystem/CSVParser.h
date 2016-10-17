#include "minicsv.h"

class CSVParser
{
public:
	void ImportCSVData()
	{
		csv::ifstream is("msft.csv");
		is.set_delimiter('\t', "##");

		if (is.is_open())
		{
		}
	};
};