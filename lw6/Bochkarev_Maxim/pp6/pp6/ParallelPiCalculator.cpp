#include "stdafx.h"
#include "ParallelPiCalculator.h"
#include <thread>
#include <vector>
#include "MonteCarloPiCalculator.h"
#include <mutex>

double ParallelPiCalculator::GetPi(const int iterNum)
{
	const unsigned int procNum = std::thread::hardware_concurrency();
	int iterationForProccess = ceil(iterNum / procNum);
	std::vector<std::thread> threads;
	double result = 0;

	for (auto i = 0; i < procNum; ++i)
	{
		threads.push_back(std::thread(ParallelPiCalculator::PiCalculationCallback, std::ref(result), iterationForProccess));
	}
	for (auto i = 0; i < threads.size(); i++)
	{
		threads.at(i).join();
	}

	return result / 4.0;
}

void ParallelPiCalculator::PiCalculationCallback(double & result, int iterNum)
{
	std::mutex mutex;
	mutex.lock();
	{
		result += CMonteCarloPiCalculator::GetPi(iterNum);
	}
	mutex.unlock();
}
