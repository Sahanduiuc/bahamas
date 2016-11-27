/*
 * Position.cpp
 *
 *  Created on: 7 Nov 2016
 *      Author: shamitha
 */

#include "Position.h"

Position::Position(int action, std::string ticker, int units,
		double price, double commission, double bid, double ask) {

}

Position::~Position() {
	// TODO Auto-generated destructor stub
}

void Position::UpdateMarketValue(double bid, double ask) {
	//TODO: Replace simple Market Value calc
	double midPointVal = (bid + ask) / 2;

}

