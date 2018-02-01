//#pragma once
//
//#include <iostream>
//
//#include <queue>
//#include <map>
//
//#include "TradingEvent.h"
//#include "PriceManager.h"
//
//#define NY (-5)
//
//class QuandlAPIPriceHandler : public PriceManager {
//public:
//	QuandlAPIPriceHandler(std::queue<TradingEvent*>& eventsQueue, std::vector<std::string>& tickers) :
//		eventsQueue(eventsQueue), tickers(tickers) {
//	}
//	~QuandlAPIPriceHandler() {}
//
//	void StreamNextEvent() {
//
//		//Collect the price data for the current day
//		if (!tradingEndedForDay) {
//			if (NYSEOpen()) {
//				for (std::string& ticker : tickers) {
//					if (!DataAvailableForMarket(ticker)) {
//						std::cout << "New price data acquired. " << ticker << " @ " << openPrice << std::endl;
//						instrumentData[ticker] = openPrice;
//						TradingEvent* tempDataFrame = new BarEvent(ticker,
//							openPrice,
//							0.0,
//							0.0,
//							0.0,
//							0.0,
//							0.0);
//						eventsQueue.push(tempDataFrame);
//					}
//					else {
//						std::cout << "No data available for ticker " << ticker << std::endl;
//					}
//				}
//				tradingEndedForDay = true;
//			}
//			else {
//				//Wait for market open
//				std::this_thread::sleep_for(std::chrono::milliseconds(1000 * 60));
//				struct tm * ptm;
//				ptm = GetTime();
//				std::cout << "Waiting for NYSE open. Current time: " <<
//					(ptm->tm_hour + NY) % 24 <<
//					":" <<
//					ptm->tm_min <<
//					std::endl;
//			}
//		}
//		else if (tradingEndedForDay) {
//			//Trading completed for current day
//			//Sleep until current trading day ends
//			std::cout << "Trading completed. System paused." << std::endl;
//			std::this_thread::sleep_for(std::chrono::milliseconds(MarketSleepTime));
//
//			//Reset flag after trading hours
//			tradingEndedForDay = false;
//			instrumentData.clear();
//		}
//	}
//
//	double GetCurrentPrice(std::string ticker) {
//		return instrumentData[ticker];
//	}
//
//	bool EOD() {
//		return false;
//	}
//private:
//	std::vector<std::string>& tickers;
//	std::queue<TradingEvent*>& eventsQueue;
//	std::map<std::string, double> instrumentData;
//
//	bool tradingEndedForDay = false;
//	double openPrice;
//	const int MarketSleepTime = (60 * 60 * 8) * 1000;
//
//	tm* GetTime() {
//		time_t rawtime;
//		struct tm * ptm;
//
//		time(&rawtime);
//
//		ptm = gmtime(&rawtime);
//
//		return ptm;
//	}
//
//	bool NYSEOpen() {
//		struct tm * ptm;
//		ptm = GetTime();
//		//printf("New York (U.S) :     %2d:%02d\n", (ptm->tm_hour + NY) % 24, ptm->tm_min);
//
//		int hour = (ptm->tm_hour + NY) % 24;
//		int mins = ptm->tm_min;
//
//		if (hour < 16) {
//			if (hour == 9 && mins > 40)
//				return true;
//			else if (hour > 9)
//				return true;
//		}
//
//		return false;
//	}
//
//	bool DataAvailableForMarket(std::string& ticker) {
//		//Get sample price data
//		//DownloadPriceData(ticker);
//
//	}
//
//};