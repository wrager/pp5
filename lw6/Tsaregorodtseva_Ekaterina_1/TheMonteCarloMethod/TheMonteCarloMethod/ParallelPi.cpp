#include "stdafx.h"
#include "ParallelPi.h"
#include <thread>

using namespace std;


CParallelPi::CParallelPi()
{
}



void CParallelPi::Calculate(long int accuracy)
{
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	srand((unsigned int)time(0));
		
	unsigned threadsNumb = std::thread::hardware_concurrency();
	std::vector<std::thread> threadsList;

	unsigned count = 0;
	for (unsigned i = 0; i < threadsNumb; i++)
	{
		threadsList.push_back(std::thread([&]() {
			count += GetNumbRightPoints(accuracy / threadsNumb); }));
	}
	for (unsigned i = 0; i < threadsNumb; i++)
	{
		if (threadsList[i].joinable())
		{
			threadsList[i].join();
		}
	}
	m_pi = (double)count / accuracy * 4;
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Time with thread: "
		<< std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
		<< " secs" << std::endl;
}

double CParallelPi::Get()
{
	return m_pi;
}

unsigned CParallelPi::GetNumbRightPoints(unsigned iteration)
{
	double x, y;
	unsigned count = 0;
	for (unsigned i = 0; i < iteration; i++)
	{
		x = (double)rand() / RAND_MAX;
		y = (double)rand() / RAND_MAX;
		if ((x*x + y*y) <= 1)
		{
			++count;
		}
	}
	return count;
}

