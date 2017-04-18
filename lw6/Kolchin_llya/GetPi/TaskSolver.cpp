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
	std::vector<std::future<ThreadResult>> m_threads;

	double result = 0.0;

	for (size_t index = 0; index < amountThreads; ++index)
	{
		m_threads.push_back(
			std::async(
				std::launch::async,
				[&]() 
				{ return ComputePi(
					index,
					amountIteration,
					amountThreads
					); 
				}
			)
		);
	}

	for (const auto & thread : m_threads)
	{
		thread.wait();
	}

	for (auto & threadResult : m_threads)
	{
		result += threadResult.get().result;
	}

	return result;
}

CTaskSolver::ThreadResult CTaskSolver::ComputePi(
	size_t threadId,
	size_t amountIteration,
	size_t amountThreads
)
{
	srand(UINT(time(NULL)) + threadId);

	double resultTheThread = 0.0;

	resultTheThread = 4.0 * CalculateHits(amountIteration / amountThreads) / amountIteration;

	std::cout << GetMessageForThread(amountIteration / amountThreads, resultTheThread, threadId) << std::endl;

	return ThreadResult(resultTheThread);
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
