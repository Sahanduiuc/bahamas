#pragma once
class BackTester
{
public:
	BackTester();
	~BackTester();

	void SimulateStrategy();

private:
	void ExecuteBacktest();
};

