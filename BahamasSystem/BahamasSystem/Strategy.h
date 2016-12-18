#ifndef STRATEGY_H_
#define STRATEGY_H_

#include <queue>
#include <numeric>

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
			event.Close,
			event.Low,
			event.Volume,
			event.AdjClose));
		
		//Add the bar to the short Window
		if (shortWindowBars.size() == shortWindow) {
			shortWindowBars.pop_front();
		}
		if (bars > (longWindow - shortWindow)) {
			shortWindowBars.push_back(BarEvent(event.GetEventTicker(),
				event.Open,
				event.High,
				event.Close,
				event.Low,
				event.Volume,
				event.AdjClose));
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
			sum += event.AdjClose;
		}

		return sum / (barQueue.size()*1.0);
	}
};

class SimpleMomentum : public Strategy {
public:
	SimpleMomentum(std::queue<TradingEvent*>& eventsQueue, std::vector<std::string> tickers) :
		Strategy(eventsQueue, tickers) {}
	void CalculateSignal(BarEvent& event) {
		bars++;
		i++;
		//Add the bar to the long Window
		if (longWindowBars.size() == windowSize) {
			//Long window full
			longWindowBars.pop_front();
		}
		longWindowBars.push_back(BarEvent(event.GetEventTicker(),
			event.Open,
			event.High,
			event.Close,
			event.Low,
			event.Volume,
			event.AdjClose));

		if (bars >= windowSize) {
			double mean = CalculateMean(longWindowBars);
			
			if (event.AdjClose > (mean * 1.01) && !isInvested) {
				//Open Long position
				TradingEvent* tempEvent = new SignalEvent(tickers[0], 1, 1);
				eventsQueue.push(tempEvent);
				isInvested = true;
				std::cout << i << " BUY signal for " << tickers[0] << " @ " << event.AdjClose << std::endl;
			}
			else if (event.AdjClose < (mean) && isInvested) {
				//Close Position
				TradingEvent* tempEvent = new SignalEvent(tickers[0], -1, 1);
				eventsQueue.push(tempEvent);
				isInvested = false;
				std::cout << i << " SELL signal for " << tickers[0] << " @ " << event.AdjClose << std::endl;
			}
		}
	}
private:
	int i = 0;
	int bars = 0;
	int windowSize = 250;
	bool isInvested = false;

	std::deque<BarEvent> longWindowBars;

	double CalculateMean(std::deque<BarEvent>& barQueue) {
		double sum = 0;

		for (BarEvent& event : barQueue) {
			sum += event.AdjClose;
		}

		return sum / (barQueue.size()*1.0);
	}
};

class SimpleBuyHold : public Strategy {
public:
	SimpleBuyHold(std::queue<TradingEvent*>& eventsQueue, std::vector<std::string> tickers) :
		Strategy(eventsQueue, tickers) {}
	void CalculateSignal(BarEvent& event) {
		if (!isInvested) {
			//Open Long position
			TradingEvent* tempEvent = new SignalEvent(tickers[0], 1, 1);
			eventsQueue.push(tempEvent);
			isInvested = true;
		}
	}

private:
	bool isInvested = false;
};

#endif
