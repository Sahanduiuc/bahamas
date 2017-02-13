#ifndef ORDERSIZER_H_
#define ORDERSIZER_H_

#include <string>

#include "Portfolio.h"
#include "OHLCVPriceManager.h"

struct MarketOrder {
	std::string Ticker;
	int Action;
	int Units;
	double price;
};

class OrderSizer
{
public:
	OrderSizer();
	~OrderSizer();

	void SizeOrder(MarketOrder&,Portfolio&);
};

#endif

