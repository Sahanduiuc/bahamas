/*
 * Position.h
 *
 *  Created on: 7 Nov 2016
 *      Author: shamitha
 */

#ifndef POSITION_H_
#define POSITION_H_

#include <string>

class Position {
public:
	Position(int, std::string, int, double, double, double, double);
	//void CalculatePositionValue();
	//void UpdateMarketValue(double, double);
	virtual ~Position();
};

#endif /* POSITION_H_ */
