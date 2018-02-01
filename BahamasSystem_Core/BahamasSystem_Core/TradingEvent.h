
#ifndef TRADINGEVENT_H_
#define TRADINGEVENT_H_

#include <string>

enum EventType { BaseEventType, BarEventType, SignalEventType, OrderEventType, FillEventType };

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

class SignalEvent : public TradingEvent {
public:
	const int action;
	const int setOrderUnits;

	SignalEvent(std::string ticker, int action, int units = 0) :
		TradingEvent(ticker, EventType::SignalEventType), action(action), setOrderUnits(units) {}
};

class OrderEvent : public TradingEvent {
public:
	const int Action;
	const int OrderUnits;

	OrderEvent(std::string ticker, int action, int units) :
		TradingEvent(ticker, EventType::OrderEventType), Action(action), OrderUnits(units) {}
};

class FillEvent : public TradingEvent {
public:
	const int Action;
	const int Units;
	const double FillPrice;
	const double Commission;

	FillEvent(std::string ticker, int action, int units, double fillPrice, double commission) :
		TradingEvent(ticker, EventType::FillEventType), Action(action), Units(units), FillPrice(fillPrice), Commission(commission) {}

};

#endif /* TRADINGEVENT_H_ */
