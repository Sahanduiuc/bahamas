#ifndef DATAIMPORTER_H_
#define DATAIMPORTER_H_

#include <vector>
#include <sstream>
#include <istream>
#include <fstream>
#include <functional>
#include <iostream>
#include <boost/coroutine/all.hpp>

class CsvImporter {
public:
	void GetDataItem(std::vector<std::string>& dataRow) {
		if (dataStream.is_open()) {
			if (dataStream.good()) {
				dataRow = csv_read_row(dataStream, ',');
			}
			else
				dataRow.clear();
		}
		else {
			dataStream.open(currentFile);

			if (dataStream.fail()) {
				std::cout << "Error importing data file" << std::endl; return;
			}

			dataRow = csv_read_row(dataStream, ',');
		}
	}

	void SetLoadFile(std::string fileName) {
		this->currentFile = dataPath + fileName;
		dataStream.close();
	}
	void SetDataPath(std::string path) {
		this->dataPath = path;
	}
private:
	std::string currentFile;
	std::ifstream dataStream;
	std::string dataPath = "";

	std::vector<std::string> csv_read_row(std::istream &in, char delimiter)
	{
		std::stringstream ss;
		bool inquotes = false;
		std::vector<std::string> row;//relying on RVO
		while (in.good())
		{
			char c = in.get();
			if (!inquotes && c == '"') //beginquotechar
			{
				inquotes = true;
			}
			else if (inquotes && c == '"') //quotechar
			{
				if (in.peek() == '"')//2 consecutive quotes resolve to 1
				{
					ss << (char)in.get();
				}
				else //endquotechar
				{
					inquotes = false;
				}
			}
			else if (!inquotes && c == delimiter) //end of field
			{
				row.push_back(ss.str());
				ss.str("");
			}
			else if (!inquotes && (c == '\r' || c == '\n'))
			{
				if (in.peek() == '\n') { in.get(); }
				row.push_back(ss.str());
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

#endif