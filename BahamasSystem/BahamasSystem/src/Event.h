/*
 * Event.h
 *
 *  Created on: 2 Nov 2016
 *      Author: shamitha
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "OHLCVDataParser.h"

enum EventType {Event,BarEvent,SignalEvent,OrderEvent};

class Event{
public:
	std::string Ticker;
	EventType Type;
};

class BarEvent: public Event{
public:
	BarEvent(std::string ticker,OHCLVDataFrame dataFrame):
		Ticker(ticker),eventData(dataFrame), Type(BarEvent) {}
	OHCLVDataFrame EventData() const{ return eventData; }
private:
	OHCLVDataFrame eventData;
};

class SignalEvent: public Event{
public:
	SignalEvent(std::string ticker,int units):
		Ticker(ticker), setOrderUnits(units), Type(SignalEvent) {}
	int GetTargetOrderUnits(){ return setOrderUnits; }
private:
	int setOrderUnits;
};

class OrderEvent: public Event{
public:
	OrderEvent(std::string ticker,int units):
		Ticker(ticker), orderUnits(units) {}
private:
	int orderUnits;
};

#endif /* EVENT_H_ */
