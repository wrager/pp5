#pragma once
#include "MonteCarloMethod.h"
class CParallelPi :
	public IMonteCarloMethod
{
public:
	CParallelPi();
	~CParallelPi() = default;
	void Calculate(long int accuracy) override;
	double Get() override;
private:
	double m_pi;
};

