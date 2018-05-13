#ifndef DATAIMPORTER_H_
#define DATAIMPORTER_H_

#include <vector>
#include <sstream>
#include <istream>
#include <fstream>
#include <functional>
#include <iostream>
#include <boost/iostreams/device/mapped_file.hpp> 

class CsvImporter {
public:
	void GetDataItem(std::vector<std::string>& dataRow) {
		uint16_t col_index = 0;

		while (*fPointer != '\n' && fPointer && fPointer != eodIndex) {
			int c = 0;
			char str[] = "                                       ";
			while (*fPointer != ',' && *fPointer != '\n' && *fPointer != '\r') {
				str[c] = fPointer[0];
				c++;
				fPointer++;
			}
			str[c] = 0;
			fPointer++;

			std::string val(str);
			dataRow.push_back(val);

			col_index++;
			if (col_index >= maxColCount)
				col_index = 0;
		}
		fPointer++;
	}

	void SetDataFile(std::string fileName) {
		this->currentFile = dataPath + fileName;
	}

	void SetDataFile(std::string fileName, int colCount) {
		SetDataFile(fileName);
		this->maxColCount = colCount;

		mmap.close();
		mmap.open(this->currentFile, boost::iostreams::mapped_file::readonly);
		fPointer = mmap.const_data();
		eodIndex = fPointer + mmap.size();
	}

	void SetDataPath(std::string path) {
		this->dataPath = path;
	}
private:
	std::string currentFile;
	std::string dataPath = "";
	int maxColCount;

	const char* fPointer = nullptr;
	const char* eodIndex = nullptr;
	boost::iostreams::mapped_file mmap;
};

#endif