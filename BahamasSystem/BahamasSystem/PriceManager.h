/*
 * PriceManager.h
 *
 *  Created on: 11 Nov 2016
 *      Author: shamitha
 */

#ifndef PRICEMANAGER_H_
#define PRICEMANAGER_H_

class PriceManager{
public:
	bool Terminate;

	virtual void StreamNextEvent() {};
};

#endif /* PRICEMANAGER_H_ */