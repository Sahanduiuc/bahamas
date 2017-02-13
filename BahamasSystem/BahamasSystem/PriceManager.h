/*
 * PriceManager.h
 *
 *  Created on: 11 Nov 2016
 *      Author: shamitha
 */

#ifndef PRICEMANAGER_H_
#define PRICEMANAGER_H_

#include <string>

class PriceManager{
public:
	bool Terminate;

	virtual void StreamNextEvent() {};
	virtual double GetCurrentPrice(std::string) {};
	virtual bool EOD() {};
	virtual std::string GetCurrentTimeStampString() {};
};

#endif /* PRICEMANAGER_H_ */
