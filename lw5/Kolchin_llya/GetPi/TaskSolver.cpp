#include "stdafx.h"
#include "TaskSolver.h"

CTaskSolver::CTaskSolver()
{
}

CTaskSolver::~CTaskSolver()
{
}

double CTaskSolver::GetPi(size_t amountIteration, size_t amountThreads)
{
	//srand(UINT(amountThreads));// TODO : transfer to other place
	srand(UINT(time(NULL)));

	double result = 0.0;//4.0 * CalculateHits(amountIteration / amountThreads) / amountIteration;
	#pragma omp for ordered schedule(dynamic)
	for (int index = 0; index < amountThreads; ++index)

	{

		result += 4.0 * CalculateHits(amountIteration / amountThreads) / amountIteration;


		//#pragma omp ordered

		//send(files[n]);

	}


	std::string message = GetFinalMessage(amountIteration, result);

	return result;
}

double CTaskSolver::RandomNumber()
{
	return double(rand()) / RAND_MAX;
}

bool CTaskSolver::InCircle(double x, double y)
{
	return (x*x + y*y) <= 1;
}

size_t CTaskSolver::CalculateHits(size_t numIter)
{
	size_t numHits = 0;
	for (size_t index = 0; index < numIter; ++index)
	{
		numHits += InCircle(RandomNumber(), RandomNumber());// TODO : see can it replace to boost function
	}
	return numHits;
}

// Evenly distributes indexes on processors
std::string CTaskSolver::GetFinalMessage(size_t amountIteration, double result)
{
	std::string message = "Id process "
		+ std::to_string(m_numberProcess) + "\n"
		+ "Amount iteration = " + std::to_string(amountIteration) + "\n"
		+ "Result = " + std::to_string(result) + "\n";

	return message;
}