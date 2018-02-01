#pragma once

#include <string.h>
#include <boost/bind.hpp>
#include "boost/date_time/gregorian/gregorian.hpp"

#include "TradingSession.h"
#include "OHLCVPriceManager.h"
#include "ExecutionManager.h"
#include "PortfolioManager.h"
#include "Strategy.h"

#ifdef BAHAMASLIBRARY_EXPORTS
#define BAHAMASLIBRARY_API __declspec(dllexport)
#else
#define BAHAMASLIBRARY_API __declspec(dllimport)
#endif

extern "C" BAHAMASLIBRARY_API TradingSession CreateSession();

extern "C" BAHAMASLIBRARY_API std::string ExecuteSession(TradingSession* session);


