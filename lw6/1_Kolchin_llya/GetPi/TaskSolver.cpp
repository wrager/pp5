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
	double result = 0.0;

	std::vector<std::thread> threads;
	std::vector<ThreadResult> threadResults(amountThreads);

	for (size_t index = 0; index < amountThreads; ++index)
	{
		threads.push_back(
			std::thread(
				[&]()
				{
					ComputePi(
						index,
						amountIteration / amountThreads,
						amountIteration,
						threadResults[index]
					);
				}
			)
		);
		
	}
	for (auto & thread : threads)
	{
		thread.join();
	}

	for (size_t index = 0; index < amountThreads; ++index)
	{
		if (!threads[index].joinable())
		{
			result += threadResults[index].result;
		}
	}
		
	return result;
}

void CTaskSolver::ComputePi(
	size_t threadId,
	size_t amountIteration,
	size_t amountPoints,
	ThreadResult & result
)
{
	srand(UINT(time(NULL) + threadId));

	double resultTheThread = 0.0;

	// Получается(для 4 потоков) 4-верть пи из-за того берём четверть точек
	// и делим на кол-во итераций

	// один поток береёт четверть точек и вычисляет коэфициент для четверти
	resultTheThread = 4.0 * CalculateHits(amountIteration) / amountPoints;

	std::cout << GetMessageForThread(amountIteration, resultTheThread, threadId) << std::endl;

	result.result = resultTheThread;
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
std::string CTaskSolver::GetMessageForThread(
	size_t amountIteration
	, double result
	, size_t indexThread
)
{
	std::string message = "Id thread "
		+ std::to_string(indexThread) + "\n"
		+ "Amount iteration = " + std::to_string(amountIteration) + "\n"
		+ "Result = " + std::to_string(result) + "\n";

	return message;
}
