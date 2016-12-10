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

#include <queue>
#include "TradingEvent.h"

//Time Zones
#define NY (-5)

class GoogleAPIPriceHandler : public PriceManager {
public:
	GoogleAPIPriceHandler(std::queue<TradingEvent*>& eventsQueue, std::string ticker):
				eventsQueue(eventsQueue) {
		this->ticker = ticker;
	}
	~GoogleAPIPriceHandler() {}

	void StreamNextEvent() {

		//Collect the price data for the current day
		if (!tradingEndedForDay) {
			//Check if NYSE is Open
			if (NYSEOpen()) {
				DownloadPriceData();
				//End trading for the current day
				tradingEndedForDay = true;
			}
		}
		else if (tradingEndedForDay) {
			//Sleep until current trading day ends
			

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
	std::string ticker;
	bool tradingEndedForDay = false;
	std::queue<TradingEvent*>& eventsQueue;
	std::map<std::string, double> instrumentData;

	void DownloadPriceData() {
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
		ss << "GET /finance/getprices?i=60&p=1d&f=d,o,h,l,c,v&df=cpct&q="+ticker+ " HTTP/1.1\r\n"
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

		std::size_t stopIndex;
		for (int i = 0; i < priceData.length(); i++) {
			if (priceData[i] == ',') {
				stopIndex = i;
				break;
			}
		}
		
		double openPrice = std::stod(result.substr(index00 + 33, stopIndex));

		instrumentData[ticker] = openPrice;

		TradingEvent* tempDataFrame = new BarEvent(ticker,
			openPrice,
			0.0,
			0.0,
			0.0,
			0.0,
			0.0);
		eventsQueue.push(tempDataFrame);
	}

	bool NYSEOpen() {
		time_t rawtime;
		struct tm * ptm;

		time(&rawtime);

		ptm = gmtime(&rawtime);
		//printf("New York (U.S) :     %2d:%02d\n", (ptm->tm_hour + NY) % 24, ptm->tm_min);
		return true;
	}
};