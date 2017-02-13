#pragma once
#define RAND_MAX 0x7fff
#include <time.h>
#include <stdlib.h>

class CMonteCarloPiCalculator
{
public:
	CMonteCarloPiCalculator();
	~CMonteCarloPiCalculator();

	static double GetPi(double numIter);

private:
	static double GetRandomNumber();
	static bool IsPoitnInCircle(double x, double y);
	static double CalculateHits(double numIter);
};

