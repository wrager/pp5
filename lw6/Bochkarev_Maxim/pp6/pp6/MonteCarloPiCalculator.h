#pragma once
#define RAND_MAX 0x7fff
#include <stdlib.h>

class CMonteCarloPiCalculator
{
public:
	CMonteCarloPiCalculator();
	~CMonteCarloPiCalculator();

	static double GetPi(double numIter);

private:
	static double GetRandomNumber();
	static bool IsPointInCircle(double x, double y);
	static double CalculateHits(double numIter);
};

