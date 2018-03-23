#pragma once

#include "..\Strategy.h"

class MACross : public Strategy {
public:
	MACross(std::queue<TradingEvent*>& eventsQueue, std::vector<std::string> tickers) :
		Strategy(eventsQueue, tickers) {}
	void CalculateSignal(BarEvent& event) {
		bars++;
		//Add the bar to the long Window
		if (longWindowBars.size() == longWindow) {
			//Long window full
			longWindowBars.pop_front();
		}
		longWindowBars.push_back(BarEvent(event.GetEventTicker(),
			event.Open,
			event.High,
			event.Low,
			event.Settle));

		//Add the bar to the short Window
		if (shortWindowBars.size() == shortWindow) {
			shortWindowBars.pop_front();
		}
		if (bars > (longWindow - shortWindow)) {
			shortWindowBars.push_back(BarEvent(event.GetEventTicker(),
				event.Open,
				event.High,
				event.Low,
				event.Settle));
		}

		//Enough bars acquired for calculating signals
		if (bars > longWindow) {
			//Calculate the moving averages
			double longMean = CalculateMean(longWindowBars);
			double shortMean = CalculateMean(shortWindowBars);

			if (shortMean > longMean && !invested) {
				//Open Long position
				TradingEvent* tempEvent = new SignalEvent(tickers[0], 1, 1);
				eventsQueue.push(tempEvent);
				invested = true;
			}
			else if (shortMean < longMean && invested) {
				//Close position
				TradingEvent* tempEvent = new SignalEvent(tickers[0], -1, 1);
				eventsQueue.push(tempEvent);
				invested = false;
			}
		}
	}
private:
	const int shortWindow = 5;
	const int longWindow = 8;
	int bars = 0;
	bool invested = false;

	std::deque<BarEvent> shortWindowBars;
	std::deque<BarEvent> longWindowBars;

	double CalculateMean(std::deque<BarEvent>& barQueue) {
		double sum = 0;

		for (BarEvent& event : barQueue) {
			sum += event.Settle;
		}

		return sum / (barQueue.size()*1.0);
	}
};

