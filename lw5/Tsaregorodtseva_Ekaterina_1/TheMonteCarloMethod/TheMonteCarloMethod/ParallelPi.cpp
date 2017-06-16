#include "stdafx.h"
#include "ParallelPi.h"

CParallelPi::CParallelPi()
{
}

void CParallelPi::Calculate(long int accuracy)
{
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	int count = 0;
	srand((unsigned int)time(0));
	double x, y;
	#pragma omp parallel for
	for (int i = 0; i < accuracy; i++) 
	{
		x = (double)rand() / RAND_MAX;
		y = (double)rand() / RAND_MAX;
		if ((x*x + y*y) <= 1) 
		{
			#pragma omp atomic
			++count;
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

