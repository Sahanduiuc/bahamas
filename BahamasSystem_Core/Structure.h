#ifndef SPREAD_H_
#define SPREAD_H_

#include "TradingEvent.h"
#include <string>

struct OptionStructure {
	std::string Id;
	std::vector<SignalEvent*> TargetPositions;
};

struct PositionStructure {

};

class OptionPriceManager;

double GetStructureValue(OptionStructure structure,OptionPriceManager& priceManager);
double GetStructureDelta(OptionStructure structure, OptionPriceManager& priceManager);
double GetStructureRegTRisk(OptionStructure structure, OptionPriceManager& priceManager);
double GetRiskAtPosition(OptionStructure structure, OptionPriceManager& priceManager, double price);

#endif

