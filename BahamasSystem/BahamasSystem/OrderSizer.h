#ifndef ORDERSIZER_H_
#define ORDERSIZER_H_

#include <string>

struct MarketOrder {
	std::string Ticker;
	int Action;
	int Units;
};

class OrderSizer
{
public:
	OrderSizer();
	~OrderSizer();

	void SizeOrder(MarketOrder&);
};

#endif

