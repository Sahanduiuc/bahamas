/*
 * Event.h
 *
 *  Created on: 2 Nov 2016
 *      Author: shamitha
 */

#ifndef TRADINGEVENT_H_
#define TRADINGEVENT_H_

#include <string>

enum EventType {BaseEventType,BarEventType,SignalEventType,OrderEventType};

class TradingEvent{
public:
	TradingEvent(std::string ticker, EventType type):
		ticker(ticker), type(type) {}
	EventType GetEventType() { return type; }

	virtual ~TradingEvent() {}
private:
	std::string ticker;
	EventType type;
};

class BarEvent: public TradingEvent{
public:
	const double Open;
	const double High;
	const double Close;
	const double Low;
	const double Volume;
	const double AdjClose;

	BarEvent(std::string ticker, double open, double high,
			double close, double low, double volume, double adjClose):
		TradingEvent(ticker, EventType::BarEventType),
		Open(open), High(high), Close(close), Low(low),
		Volume(volume), AdjClose(adjClose) {}

	virtual ~BarEvent() {}
};

class SignalEvent: public TradingEvent{
public:
	SignalEvent(std::string ticker,int units):
		TradingEvent(ticker, EventType::SignalEventType), setOrderUnits(units) {}
	int GetTargetOrderUnits(){ return setOrderUnits; }
private:
	int setOrderUnits;
};

class OrderEvent: public TradingEvent{
public:
	OrderEvent(std::string ticker,int units):
		TradingEvent(ticker, EventType::OrderEventType), orderUnits(units) {}
private:
	int orderUnits;
};

#endif /* TRADINGEVENT_H_ */
