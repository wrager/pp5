#pragma once
#include "MonteCarloMethod.h"
class CLinearPi :
	public IMonteCarloMethod
{
public:
	CLinearPi();
	~CLinearPi() = default;
	void Calculate(long int accuracy) override;
	double Get() override;
private:
	double m_pi;
};

