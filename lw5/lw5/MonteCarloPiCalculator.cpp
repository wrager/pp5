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
	double result = 4.0 * (double)CalculateHits(numIter) / numIter;
	return result;
}

double CMonteCarloPiCalculator::GetRandomNumber()
{
	return (double)rand() / RAND_MAX;
}

bool CMonteCarloPiCalculator::IsPoitnInCircle(double x, double y)
{
	return (x * x + y * y) <= 1;
}

double CMonteCarloPiCalculator::CalculateHits(double numIter)
{
	double hitsAmount = 0;
	
	#pragma omp parallel num_threads(omp_get_num_procs()) 
	{
		#pragma omp for reduction(+:hitsAmount)
		for (int i = 0; i < (int)numIter; ++i) {
			hitsAmount += IsPoitnInCircle(GetRandomNumber(), GetRandomNumber());
		}
	}
	
	return hitsAmount;
}