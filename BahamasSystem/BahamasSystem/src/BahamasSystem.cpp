//============================================================================
// Name        : BahamasSystem.cpp
// Author      : Shamitha
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "OHLCVDataParser.h"


using namespace std;

int main() {

	OHLCVDataParser ohclvParser;
	ohclvParser.ImportInstrumentData("msft");

	std::cout << "fdf";

	return 0;
}
