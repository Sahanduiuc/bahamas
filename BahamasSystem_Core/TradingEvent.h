#ifndef TRADINGEVENT_H_
#define TRADINGEVENT_H_

#include <string>
#include "DataFrames.h"
#include "OptionChain.h"

enum EventType { BaseEventType, OrderBookUpdateEventType , BarEventType, SignalEventType, OrderEventType, FillEventType, OptionChainUpdateEventType };

class TradingEvent {
public:
	TradingEvent(std::string ticker, EventType type) :
		ticker(ticker), type(type) {}
	EventType GetEventType() const { return type; }
	std::string GetEventTicker() const { return ticker; }

	virtual ~TradingEvent() {}
private:
	std::string ticker;
	EventType type;
};

class BarEvent : public TradingEvent {
public:
	const double Open;
	const double High;
	const double Low;
	const double Settle;

	BarEvent(std::string ticker, double open, double high,
		double low, double settle) :
		TradingEvent(ticker, EventType::BarEventType),
		Open(open), High(high), Low(low), Settle(settle) {}

	~BarEvent() {}
};

class OrderBookUpdateEvent : public TradingEvent {
public:
	const double Bid;
	const double BidSize;
	const double Ask;
	const double AskSize;

	OrderBookUpdateEvent(std::string ticker, double bid, double bidsize,
		double ask, double asksize) :
		TradingEvent(ticker, EventType::BarEventType),
		Bid(bid), BidSize(bidsize), Ask(ask), AskSize(asksize) {}

	~OrderBookUpdateEvent() {}
};


class SignalEvent : public TradingEvent {
public:
	const int action;
	const int setOrderUnits;
	const int tradeId;

	SignalEvent(std::string ticker, int action, int units, int tradeId) :
		TradingEvent(ticker, EventType::SignalEventType), 
		action(action), setOrderUnits(units), tradeId(tradeId) {}
};

class OrderEvent : public TradingEvent {
public:
	const int Action;
	const int OrderUnits;
	const int tradeId;

	OrderEvent(std::string ticker, int action, int units, int tradeId) :
		TradingEvent(ticker, EventType::OrderEventType), 
		Action(action), OrderUnits(units), tradeId(tradeId) {}
};

class FillEvent : public TradingEvent {
public:
	const int Action;
	const int Units;
	const double FillPrice;
	const double Commission;
	const int tradeId;

	FillEvent(std::string ticker, int action, int units, double fillPrice, 
		double commission, int tradeId) :
		TradingEvent(ticker, EventType::FillEventType), 
		Action(action), Units(units), FillPrice(fillPrice), 
		Commission(commission), tradeId(tradeId) {}

};

class OptionChainUpdateEvent : public TradingEvent {
public:
	std::vector<OptionChain*> OptionChains;

	OptionChainUpdateEvent(std::string underlyingTicker):
		TradingEvent(underlyingTicker, EventType::OptionChainUpdateEventType){}
};

#endif /* TRADINGEVENT_H_ */
