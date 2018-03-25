#pragma once

#include "..\Strategy.h"

class FundOfFunds : public Strategy {
public:
	FundOfFunds(std::queue<TradingEvent*>& eventsQueue, std::vector<std::string> tickers,
		std::string fundHoldingsFile, OHLCVPriceManager& priceManager) :
		Strategy(eventsQueue, tickers), priceManager(priceManager) {
		CsvImporter csvImporter;
		csvImporter.SetLoadFile(fundHoldingsFile);

		std::vector<std::string> dataRow;

		csvImporter.GetDataItem(dataRow);
		while (!dataRow.empty()) {
			boost::gregorian::date eventDate =
				boost::gregorian::from_string(dataRow[0]);

			holdingsHistory[eventDate].insert(dataRow[1]);

			csvImporter.GetDataItem(dataRow);
		}
	}

	void CalculateSignal(BarEvent& event) {

		std::string ticker = event.GetEventTicker();
		if (holdingsHistory.find(priceManager.GetCurrentTimeStamp()) != holdingsHistory.end()) {

			//If the current ticker is present in the current holdings period
			if (holdingsHistory[priceManager.GetCurrentTimeStamp()].find(ticker) !=
				holdingsHistory[priceManager.GetCurrentTimeStamp()].end()) {

				//If instrument is not invested
				if (investedStatus.find(ticker) == investedStatus.end() ||
					!investedStatus[ticker]) {

					//Open Long position
					TradingEvent* tempEvent = new SignalEvent(ticker, 1, 0);
					eventsQueue.push(tempEvent);
					investedStatus[ticker] = true;
					std::cout << priceManager.GetCurrentTimeStampString()
						<< " LONG signal " << ticker << " @ " << event.Settle << std::endl;

					investedStatus[ticker] = true;
				}
			}
			else {
				//If the current ticker is already invested
				//but not present in the current holdings period
				if (investedStatus.find(ticker) != investedStatus.end() &&
					investedStatus[ticker]) {
					//Sell positions of current instrument
					TradingEvent* tempEvent = new SignalEvent(ticker, -1, 0);
					eventsQueue.push(tempEvent);
					investedStatus[ticker] = false;

					investedStatus[ticker] = false;
				}
			}
		}
	}

private:
	std::map<boost::gregorian::date, std::unordered_set<std::string> > holdingsHistory;
	std::map<std::string, bool> investedStatus;
	OHLCVPriceManager& priceManager;
};

