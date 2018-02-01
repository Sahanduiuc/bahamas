#ifndef RISHMANAGER_H_
#define RISHMANAGER_H_

#include <vector>
#include "OrderSizer.h"

class RiskManager
{
public:
	RiskManager();
	~RiskManager();

	std::vector<MarketOrder> ProfileOrder(MarketOrder&);
};

#endif

