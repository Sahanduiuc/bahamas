#include "stdafx.h"
#include "OptionPriceManager.h"
#include "Structure.h"

double GetStructureValue(OptionStructure structure, 
	OptionPriceManager& priceManager) {
	double totValue = 0.0;

	for (int i = 0; i < structure.TargetPositions.size(); i++) {
		totValue += 
			priceManager.GetCurrentPrice(structure.TargetPositions[i]->GetEventTicker()) *			
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
	double maxRisk = -1;

	for (int i = 0; i < structure.TargetPositions.size(); i++) {
		OptionContract* contract = priceManager.
			OptionContracts[structure.TargetPositions[i]->GetEventTicker()];

		double risk = GetRiskAtPosition(structure, priceManager, contract->Strike);
		if (risk > maxRisk)
			maxRisk = risk;
	}

	return maxRisk;
}

double GetRiskAtPosition(OptionStructure structure,
	OptionPriceManager& priceManager, double price) {
	double riskVal = 0.0;

	for (int i = 0; i < structure.TargetPositions.size(); i++) {
		OptionContract* contract = priceManager.
			OptionContracts[structure.TargetPositions[i]->GetEventTicker()];
		int units = structure.TargetPositions[i]->setOrderUnits;
		int action = structure.TargetPositions[i]->action;
		//TODO Handle Calls
		if (contract->Type == 'P') {
			riskVal += priceManager.GetCurrentPrice(contract->Id) * action * units;
			if(price < contract->Strike)
				riskVal += (contract->Strike - price) * units * action * -1 * 1000;
		}
	}

	return riskVal;
}
