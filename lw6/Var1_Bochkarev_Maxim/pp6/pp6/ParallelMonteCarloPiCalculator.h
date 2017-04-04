#pragma once
#include "AbstractMonteCarloPiCalculator.h"

class ParallelMonteCarloPiCalculator: AbstractMonteCarloPiCalculator
{
public:
	static double GetPi(const int iterNum);
private:
	static void PiCalculationCallback(double& result, int iterNum);
};
