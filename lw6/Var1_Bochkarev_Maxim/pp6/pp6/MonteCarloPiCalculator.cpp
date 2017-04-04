#include "stdafx.h"
#include "MonteCarloPiCalculator.h"


CMonteCarloPiCalculator::CMonteCarloPiCalculator()
{
}


CMonteCarloPiCalculator::~CMonteCarloPiCalculator()
{
}

double CMonteCarloPiCalculator::GetPi(double numIter)
{
	srand(time(NULL));
	double result = 4.0 * double(CalculateHits(numIter)) / numIter;
	return result;
}

double CMonteCarloPiCalculator::GetRandomNumber()
{
	return double(rand()) / RAND_MAX;
}

bool CMonteCarloPiCalculator::IsPointInCircle(double x, double y)
{
	return (x * x + y * y) <= 1;
}

double CMonteCarloPiCalculator::CalculateHits(double numIter)
{
	double hitsAmount = 0;
	
	for (int i = 0; i < int(numIter); ++i) {
		hitsAmount += IsPointInCircle(GetRandomNumber(), GetRandomNumber());
	}
	
	return hitsAmount;
}