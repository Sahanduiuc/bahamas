#include "stdafx.h"
#include "OrderSizer.h"

OrderSizer::OrderSizer()
{
}

OrderSizer::~OrderSizer()
{
}

//Basic Position Sizing
void OrderSizer::SizeOrder(MarketOrder& order, Portfolio& portfolio) {

	//TODO
	//CURRENT: Allocate each instrument 10% of the equity
	if (order.Units == 0) {

		if (order.Action == 1) {
			order.Units = (portfolio.GetEquityValue() * 0.1) / order.price;
		}
		else if (order.Action == -1) {
			order.Units = portfolio.GetInvestedPositions()[order.Ticker].Units();
		}

	}
}