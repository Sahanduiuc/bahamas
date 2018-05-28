#ifndef PRICEMANAGER_H_
#define PRICEMANAGER_H_

#include <string>

class PriceManager {
public:
	PriceManager() {};

	bool Terminate;

	virtual void StreamNextEvent() = 0;
	virtual double GetCurrentPrice(std::string) = 0;
	virtual bool EOD() = 0;
	virtual std::string GetCurrentTimeStampString() = 0;
	virtual OptionDataFrame GetCurrentDataFrame(std::string) = 0;
};

#endif