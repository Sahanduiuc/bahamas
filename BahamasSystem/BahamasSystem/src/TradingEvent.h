/*
 * Event.h
 *
 *  Created on: 2 Nov 2016
 *      Author: shamitha
 */

#ifndef TRADINGEVENT_H_
#define TRADINGEVENT_H_

#include <string>

enum EventType {Event,BarEvent,SignalEvent,OrderEvent};

class TradingEvent{
public:
	TradingEvent(std::string ticker, EventType type):
		ticker(ticker), type(type) {}
	EventType GetEventType() { return type; }
private:
	std::string ticker;
	EventType type;
};

//TODO Add bar data (OHCLV)
class BarEvent: public TradingEvent{
public:
	BarEvent(std::string ticker):
		TradingEvent(ticker, EventType::BarEvent) {};
	//OHCLVDataFrame EventData() const{ return eventData; }
private:
	//OHCLVDataFrame eventData;
};

class SignalEvent: public TradingEvent{
public:
	SignalEvent(std::string ticker,int units):
		TradingEvent(ticker, EventType::SignalEvent), setOrderUnits(units) {}
	int GetTargetOrderUnits(){ return setOrderUnits; }
private:
	int setOrderUnits;
};

class OrderEvent: public TradingEvent{
public:
	OrderEvent(std::string ticker,int units):
		TradingEvent(ticker, EventType::OrderEvent), orderUnits(units) {}
private:
	int orderUnits;
};

#endif /* TRADINGEVENT_H_ */
