#include "stdafx.h"
#include "LinearPi.h"


CLinearPi::CLinearPi()
{
}

void CLinearPi::Calculate(long int accuracy)
{
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	srand((unsigned int)time(0));
	int count = 0;
	double x, y;
	for (int i = 0; i < accuracy; i++) 
	{
		x = (double)rand() / RAND_MAX;
		y = (double)rand() / RAND_MAX;
		if ((x*x + y*y) <= 1) ++count;
	}
	m_pi = (double)count / accuracy * 4;

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Time without thread: "
		<< std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
		<< " secs" << std::endl;
}

double CLinearPi::Get()
{
	return m_pi;
}
