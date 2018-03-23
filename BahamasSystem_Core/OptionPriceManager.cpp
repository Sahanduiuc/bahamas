#include "stdafx.h"
#include "OptionPriceManager.h"

OptionPriceManager::OptionPriceManager(std::queue<TradingEvent*>& eventsQueue,
	std::string ticker,
	boost::gregorian::date& startDate,
	boost::gregorian::date& endDate) :
	eventsQueue(eventsQueue) {

	this->currentPeriod = startDate;
	this->endPeriod = endDate;

	std::cout << "All Option chains for symbol " << ticker << " successfully loaded." << std::endl;
}

void OptionPriceManager::ImportInstrumentData(std::string ticker) {

}