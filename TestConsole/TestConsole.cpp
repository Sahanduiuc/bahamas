// TestConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "BahamasSystemCore.h"
//
//#include "spdlog\spdlog.h"

int main()
{

	TradingSession t_session = CreateSession();
	//auto s = ExecuteSession(&t_session);
	//std::cout << s;

	int i = 0;
	std::cin >> i;
    return 0;
}

