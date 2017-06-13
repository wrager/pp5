#include "stdafx.h"
#include "ParallelMonteCarloPiCalculator.h"
#include <thread>
#include <vector>
#include "MonteCarloPiCalculator.h"
#include <mutex>

double ParallelMonteCarloPiCalculator::GetPi(const int iterNum)
{
	const unsigned int procNum = std::thread::hardware_concurrency();
	int iterationForProccess = ceil(iterNum / procNum);
	std::vector<std::thread> threads;
	double result = 0;

	for (auto i = 0; i < procNum; ++i)
	{
		threads.push_back(std::thread(ParallelMonteCarloPiCalculator::PiCalculationCallback, std::ref(result), iterationForProccess));
	}
	for (auto i = 0; i < threads.size(); i++)
	{
		threads.at(i).join();
	}

	return result / procNum;
}

void ParallelMonteCarloPiCalculator::PiCalculationCallback(double & result, int iterNum)
{
	std::mutex mutex;
	mutex.lock();
	{
		result += CMonteCarloPiCalculator::GetPi(iterNum);
	}
	mutex.unlock();
}
