#include "stdafx.h"
#include <random>
#include <iostream>
#include <iomanip>
#include <omp.h>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;

int RandInt(int max)
{
	return int(rand() % max);
}

float CalculatePi(size_t iterationsCount)
{
	int rad = 1000;
	int includedPoints = 0;
	for (unsigned int i = 0; i < iterationsCount; ++i)
	{
		int x = RandInt(rad);
		int y = RandInt(rad);
		if (rad * rad >= x * x + y * y)
		{
			includedPoints++;
		}
	}

	return float(4.f * (float(includedPoints) / float(iterationsCount)));
}

void PiCalculationCallback(double & result, int iterationsCount)
{
	mutex mutex;
	mutex.lock();
	{
		result += CalculatePi(iterationsCount);
	}
	mutex.unlock();
}

double CalculatePiParall(int iterationsCount)
{	
	const unsigned int processCount = thread::hardware_concurrency(); 
	int iterationForProccess = ceil(iterationsCount / processCount);
	vector<thread> threads;
	double result = 0;

	for (auto i = 0; i < processCount; ++i)
	{
		threads.push_back(thread(PiCalculationCallback, ref(result), iterationForProccess));
	}
	for (auto i = 0; i < threads.size(); ++i)
	{
		threads[i].join();
	}

	return result / processCount;
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << "Wrong arguments! Enter the number of iterations!" << endl;
		return 1;
	}

	cout << "Parallel method" << endl;
	auto startTimeParallel = clock();
	auto resultParallel = CalculatePiParall(size_t(argv[1]));
	cout << "The number Pi: " << resultParallel << endl;
	auto endTimeParallel = clock();
	auto countingTimeParallel = endTimeParallel - startTimeParallel;
	cout << "Counting time: " << countingTimeParallel / (CLOCKS_PER_SEC / 1000) << " milliseconds" << endl << endl;

	cout << "Sequential method" << endl;
	double startTimeSequential = clock();
	double resultSequential = CalculatePi(size_t(argv[1]));
	cout << "The number Pi: " << resultSequential << endl;
	double endTimeSequential = clock();
	double countingTimeSequential = endTimeSequential - startTimeSequential;
	cout << "Counting time: " << countingTimeSequential / (CLOCKS_PER_SEC / 1000) << " milliseconds" << endl;

	return 0;
}