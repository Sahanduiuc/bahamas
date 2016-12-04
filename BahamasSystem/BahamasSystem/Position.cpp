/*
 * Position.cpp
 *
 *  Created on: 7 Nov 2016
 *      Author: shamitha
 */

#include "Position.h"

Position::Position(int action, std::string ticker, int units,
		double price, double commission, double bid, double ask):
		action(action), ticker(ticker), totalUnits(units), price(price), totalCommission(commission) {
	CalculatePositionValue();
	UpdateMarketValue(bid, ask);
}

Position::~Position() {
	// TODO Auto-generated destructor stub
}

void Position::CalculatePositionValue() {
	if (action == 1) {
		unitsBought = totalUnits;
		avgBuyValue = price;
		totalBuyValue = unitsBought * price;
		avgValue = ((price * totalUnits) + totalCommission) / totalUnits;
		costBasis = totalUnits * avgValue;
	}
	else if (action == -1) {
		unitsSold = totalUnits;
		avgSellValue = price;
		totalSellValue = unitsSold * price;
		avgValue = ((price * totalUnits) - totalCommission) / totalUnits;
		costBasis = (totalUnits * avgValue) * -1.0;
	}
	netUnits = unitsBought - unitsSold;
	netValue = totalSellValue - totalBuyValue;
	netValueAfterCommission = netValue - totalCommission;
}

void Position::UpdateMarketValue(double bid, double ask) {
	//TODO: Replace simple Market Value calc
	double midPointVal = (bid + ask) / 2;
	marketValue = totalUnits * midPointVal * sign(netUnits);
	unrealisedPnL = marketValue - costBasis;
	realisedPnL = marketValue + netValueAfterCommission;
}

void Position::ModifyPosition(int action, int units, double price,
								double commission) {
	this->totalCommission += commission;

	if (action == 1) {
		avgBuyValue = ((avgBuyValue * unitsBought) + (price * units)) / (units + unitsBought);
		avgValue = ((avgValue * unitsBought) + (price * units) + commission) / (units + unitsBought);
		unitsBought += units;
		totalBuyValue = unitsBought * avgBuyValue;
	}
	else if (action == -1) {
		avgSellValue = ((avgSellValue * unitsSold) + (price * units)) / (units + unitsSold);
		avgValue = ((avgValue * unitsSold) + (price * units) - commission) / (units + unitsSold);
		unitsSold += units;
		totalSellValue = unitsSold * avgSellValue;
	}

	netUnits = unitsBought - unitsSold;
	totalUnits = netUnits;
	netValue = totalSellValue - totalBuyValue;
	netValueAfterCommission = netValue - totalCommission;
	costBasis = totalUnits * avgValue;
}

