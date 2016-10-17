#include "stdafx.h"
#include "CppUnitTest.h"
#include <CSVParser.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			CSVParser csvParser;
			csvParser.ImportCSVData();
		}

	};
}