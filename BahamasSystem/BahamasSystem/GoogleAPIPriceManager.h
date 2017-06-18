#include <iostream>
#include <ctype.h>
#include <cstring>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <string>
#include <time.h>
#include <chrono>
#include <thread>

#include <queue>
#include "TradingEvent.h"

//Time Zones
#define NY (-5)

class GoogleAPIPriceHandler : public PriceManager {
public:
	GoogleAPIPriceHandler(std::queue<TradingEvent*>& eventsQueue, std::vector<std::string>& tickers):
				eventsQueue(eventsQueue), tickers(tickers) {
	}
	~GoogleAPIPriceHandler() {}

	void StreamNextEvent() {
		int i = 0;
		//Collect the price data for the current day
		if (!tradingEndedForDay) {

			if (NYSEOpen()) {
				for (std::string& ticker : tickers) {
					if (!DataAvailableForMarket(ticker)) {
						std::cout << i << " New price data acquired. " << ticker << " @ " << openPrice << std::endl;
						i++;
						instrumentData[ticker] = openPrice;
						TradingEvent* tempDataFrame = new BarEvent(ticker,
							openPrice,
							0.0,
							0.0,
							0.0);
						eventsQueue.push(tempDataFrame);
					}
					else {
						std::cout << "No data available for ticker " << ticker << std::endl;
					}
					if (i % 500 == 0) {
						std::cout << "Reset data collection." << std::endl;
						std::this_thread::sleep_for(std::chrono::milliseconds(1000 * 60 * 5));
					}
				}
				tradingEndedForDay = true;
			}
			else {
				//Wait for market open
				std::this_thread::sleep_for(std::chrono::milliseconds(1000 * 60));
				struct tm * ptm;
				ptm = GetTime();
				std::cout << "Waiting for NYSE open. Current time: " <<
					(ptm->tm_hour + NY) % 24 <<
					":" <<
					ptm->tm_min <<
					std::endl;
			}
		}
		else if (tradingEndedForDay) {
			//Trading completed for current day
			//Sleep until current trading day ends
			std::cout << "Trading completed. System paused." << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(MarketSleepTime));

			//Reset flag after trading hours
			tradingEndedForDay = false;
			instrumentData.clear();
		}
	}
	
	double GetCurrentPrice(std::string ticker) {
		return instrumentData[ticker];
	}
	
	bool EOD() {
		return false;
	}

private:
	std::vector<std::string>& tickers;
	bool tradingEndedForDay = false;
	std::queue<TradingEvent*>& eventsQueue;
	std::map<std::string, double> instrumentData;
	time_t currentPriceDate;
	double openPrice;

	const int MarketSleepTime = (60 * 60 * 8) * 1000;

	void DownloadPriceData(std::string& ticker) {
		//Dowload Price Data
		int sock;
		struct sockaddr_in client;
		int PORT = 80;

		struct hostent * host = gethostbyname("www.google.com");

		if ((host == NULL) || (host->h_addr == NULL)) {
			std::cout << "Error retrieving DNS information.";
			exit(1);
		}

		bzero(&client, sizeof(client));
		client.sin_family = AF_INET;
		client.sin_port = htons(PORT);
		memcpy(&client.sin_addr, host->h_addr, host->h_length);

		sock = socket(AF_INET, SOCK_STREAM, 0);

		if (sock < 0) {
			std::cout << "Error creating socket.";
			exit(1);
		}

		if (connect(sock, (struct sockaddr *)&client, sizeof(client)) < 0) {
			close(sock);
			std::cout << "Could not connect";
			exit(1);
		}
		std::stringstream ss;
		ss << "GET /finance/getprices?i=60&p=1d&f=d,o,h,l,c,v&df=cpct&q=" + ticker + " HTTP/1.1\r\n"
			<< "Host: www.google.com\r\n"
			<< "Connection: close\r\n"
			<< "\r\n\r\n";
		std::string request = ss.str();

		if (send(sock, request.c_str(), request.length(), 0) != (int)request.length()) {
			std::cout << "Error sending request.";
			exit(1);
		}

		std::stringstream resultsStream;
		char cur;
		while (read(sock, &cur, 1) > 0) {
			resultsStream << cur;
		}
		std::string result = resultsStream.str();

		std::size_t index00 = result.find("TIMEZONE_OFFSET=-300");
		std::string priceData = result.substr(index00 + 33, 15);

		std::size_t stopIndex = -1;
		for (int i = 0; i < priceData.length(); i++) {
			if (priceData[i] == ',') {
				stopIndex = i;
				break;
			}
		}

		if (stopIndex != -1) {
			openPrice = std::stod(result.substr(index00 + 33, stopIndex));
			//Get Unix Time
			currentPriceDate = std::stoi(result.substr(index00 + 22, 10));
		}
		else {
			openPrice = 0;
			currentPriceDate = 1481999258;
		}
	}

	bool NYSEOpen() {
		struct tm * ptm;
		ptm = GetTime();
		//printf("New York (U.S) :     %2d:%02d\n", (ptm->tm_hour + NY) % 24, ptm->tm_min);
		
		int hour = (ptm->tm_hour + NY) % 24;
		int mins = ptm->tm_min;

		if (hour < 16) {
			if(hour == 9 && mins > 40)
				return true;
			else if (hour > 9)
				return true;
		}
		
		return false;
	}

	tm* GetTime() {
		time_t rawtime;
		struct tm * ptm;

		time(&rawtime);

		ptm = gmtime(&rawtime);

		return ptm;
	}

	bool DataAvailableForMarket(std::string& ticker) {

		//Get sample price data
		DownloadPriceData(ticker);

		tm* current = GetTime();

		int year = (current->tm_year)+1900, month = (current->tm_mon) + 1, day = current->tm_mday, hour = 14, min = 35, sec = 0;

		struct tm* priceDate = gmtime(&currentPriceDate);

		if (day == priceDate->tm_mday)
			return true;

		return false;
	}
};