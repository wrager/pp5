#pragma once

class ParallelPiCalculator
{
public:
	static double GetPi(const int iterNum);
private:
	static void PiCalculationCallback(double& result, int iterNum);
};
