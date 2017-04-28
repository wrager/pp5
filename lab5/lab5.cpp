#include "stdafx.h"
#include <random>
#include <iostream>
#include <iomanip>

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

int main(int argc, char** argv)
{
	double startTime = clock();
	double result = CalculatePi(size_t(argv[1]));
	cout << "The number Pi: " << result << endl;
	double endTime = clock();
	double countingTime = endTime - startTime;
	cout << "Counting time: " << countingTime / CLOCKS_PER_SEC << " seconds" << endl;

	return 0;
}