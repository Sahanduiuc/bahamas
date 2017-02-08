#ifndef STRATEGY_H_
#define STRATEGY_H_

#include <queue>
#include <numeric>
#include <map>

#include "TradingEvent.h"

class Strategy {
public:
	const std::vector<std::string> tickers;

	Strategy(std::queue<TradingEvent*>& eventsQueue, std::vector<std::string> tickers):
		eventsQueue(eventsQueue), tickers(tickers) {};
	virtual void CalculateSignal(BarEvent& event) = 0;
protected:
	std::queue<TradingEvent*>& eventsQueue;
};

class TestStrategy : public Strategy {
public:
	TestStrategy(std::queue<TradingEvent*>& eventsQueue, std::vector<std::string> tickers):
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
				TradingEvent* tempEvent = new SignalEvent(tickers[0],1,1);
				eventsQueue.push(tempEvent);
				invested = true;
			}
			else if (shortMean < longMean && invested) {
				//Close position
				TradingEvent* tempEvent = new SignalEvent(tickers[0], -1,1);
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

class SimpleBuyHold : public Strategy {
public:
	SimpleBuyHold(std::queue<TradingEvent*>& eventsQueue, std::vector<std::string> tickers) :
		Strategy(eventsQueue, tickers) {
		for (auto ticker : tickers) {
			investedStatus[ticker] = false;
		}
	}
	void CalculateSignal(BarEvent& event) {
		if (!investedStatus[event.GetEventTicker()]) {
			//Open Long position
			TradingEvent* tempEvent = new SignalEvent(event.GetEventTicker(), 1, 1);
			eventsQueue.push(tempEvent);
			investedStatus[event.GetEventTicker()] = true;
		}
	}

private:
	std::map<std::string, bool> investedStatus;
};

#endif
