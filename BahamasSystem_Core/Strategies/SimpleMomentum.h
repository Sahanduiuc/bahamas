#pragma once

#include "..\Strategy.h"

class SimpleMomentum : public Strategy {
public:
	SimpleMomentum(std::queue<TradingEvent*>& eventsQueue, std::vector<std::string> tickers) :
		Strategy(eventsQueue, tickers) {
		for (auto ticker : tickers) {
			investedStatus[ticker] = false;
			bars[ticker] = 0;
			longWindowBars[ticker].clear();
		}
	}
	void CalculateSignal(BarEvent& event) {

		std::string selectedTicker = event.GetEventTicker();

		bars[selectedTicker]++;
		//Add the bar to the long Window
		if (longWindowBars[selectedTicker].size() == windowSize) {
			//Long window full
			longWindowBars[selectedTicker].pop_front();
		}
		longWindowBars[selectedTicker].push_back(BarEvent(selectedTicker,
			event.Open,
			event.High,
			event.Low,
			event.Settle));

		if (bars[selectedTicker] >= windowSize) {
			double mean = CalculateMean(longWindowBars[selectedTicker]);

			if (event.Settle > (mean * 1.1) && !investedStatus[selectedTicker]) {
				//Open Long position
				TradingEvent* tempEvent = new SignalEvent(selectedTicker, 1, 1);
				eventsQueue.push(tempEvent);
				investedStatus[selectedTicker] = true;
				std::cout << bars[selectedTicker] << " BUY signal for " << selectedTicker << " @ " << event.Settle << std::endl;
			}
			else if (event.Settle < (mean) && investedStatus[selectedTicker]) {
				//Close Position
				TradingEvent* tempEvent = new SignalEvent(selectedTicker, -1, 1);
				eventsQueue.push(tempEvent);
				investedStatus[selectedTicker] = false;
				std::cout << bars[selectedTicker] << " SELL signal for " << selectedTicker << " @ " << event.Settle << std::endl;
			}
		}
	}
private:
	std::map<std::string, int> bars;
	int windowSize = 50;
	std::map<std::string, bool> investedStatus;
	std::map<std::string, std::deque<BarEvent> > longWindowBars;

	double CalculateMean(std::deque<BarEvent>& barQueue) {
		double sum = 0;

		for (BarEvent& event : barQueue) {
			sum += event.Settle;
		}

		return sum / (barQueue.size()*1.0);
	}
};