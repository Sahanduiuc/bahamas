#include "OrderSizer.h"

OrderSizer::OrderSizer()
{
}

OrderSizer::~OrderSizer()
{
}

//Basic Order Sizing
void OrderSizer::SizeOrder(MarketOrder& order) {
	if (order.Units == 0)
		order.Units = 1;
}