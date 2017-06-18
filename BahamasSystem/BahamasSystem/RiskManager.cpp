#include "RiskManager.h"

RiskManager::RiskManager()
{
}


RiskManager::~RiskManager()
{
}

std::vector<MarketOrder> RiskManager::ProfileOrder(MarketOrder& order) {
	std::vector<MarketOrder> results;
	results.push_back(order);
	
	return results;
}