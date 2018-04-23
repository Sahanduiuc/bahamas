#include "stdafx.h"
#include "OptionPriceManager.h"
#include "Structure.h"

double GetStructureValue(OptionStructure structure, 
	OptionPriceManager& priceManager) {
	double totValue = 0.0;

	for (int i = 0; i < structure.TargetPositions.size(); i++) {
		totValue += priceManager.GetCurrentPrice(
			structure.TargetPositions[i]->GetEventTicker()) *			
			structure.TargetPositions[i]->action *
			structure.TargetPositions[i]->setOrderUnits;
	}

	return totValue;
}

double GetStructureDelta(OptionStructure structure,
	OptionPriceManager& priceManager) {
	double totDelta = 0.0;

	for (int i = 0; i < structure.TargetPositions.size(); i++) {
		totDelta += priceManager.GetCurrentDataFrame(
			structure.TargetPositions[i]->GetEventTicker()).Delta *
			structure.TargetPositions[i]->action *
			structure.TargetPositions[i]->setOrderUnits;
	}

	return totDelta;
}

double GetStructureRegTRisk(OptionStructure structure,
	OptionPriceManager& priceManager) {
	return 0.0;
}
