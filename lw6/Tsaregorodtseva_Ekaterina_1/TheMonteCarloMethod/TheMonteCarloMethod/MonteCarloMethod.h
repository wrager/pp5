#pragma once
class IMonteCarloMethod
{
public:
	virtual ~IMonteCarloMethod() = default;
	virtual double Get() = 0;
	virtual void Calculate(long int accuracy) = 0;
};

