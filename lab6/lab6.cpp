#include "stdafx.h"
#include <random>
#include <iostream>
#include <iomanip>
#include <vector>

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
	if (argc != 2)
	{
		cout << "Wrong arguments! Enter the number of iterations!" << endl;
		return 1;
	}

	cout << "Sequential method" << endl;
	double startTimeSequential = clock();
	double resultSequential = CalculatePi(size_t(argv[1]));
	cout << "The number Pi: " << resultSequential << endl;
	double endTimeSequential = clock();
	double countingTimeSequential = endTimeSequential - startTimeSequential;
	cout << "Counting time: " << countingTimeSequential / (CLOCKS_PER_SEC / 1000) << " milliseconds" << endl;

	return 0;
}