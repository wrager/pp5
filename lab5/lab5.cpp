#include "stdafx.h"
#include <random>
#include <iostream>
#include <iomanip>
#include <omp.h>

using namespace std;

int RandInt(int max)
{
	return int(rand() % max);
}

float CalculatePiSequential(size_t iterationsCount)
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

float CalculatePiParall(size_t iterationsCount)
{
	srand(unsigned int(time(0)));
	int rad = 1000;
	int includedPoints = 0;
	#pragma omp parallel num_threads(omp_get_num_procs()) 
		{
		#pragma omp parallel for private (x), reduction (+:sum)
			for (unsigned int i = 0; i < iterationsCount; ++i)
			{
				int x = RandInt(rad);
				int y = RandInt(rad);
				if (rad * rad >= x * x + y * y)
				{
					includedPoints++;
				}
			}
		}

	return float(4.f * (float(includedPoints) / float(iterationsCount)));
}

int main(int argc, char** argv)
{
	cout << "Parallel method" << endl;
	auto startTimeParallel = omp_get_wtime();
	auto resultParallel = CalculatePiParall(size_t(argv[1]));
	cout << "The number Pi: " << resultParallel << endl;
	auto endTimeParallel = omp_get_wtime();
	auto countingTimeParallel = endTimeParallel - startTimeParallel;
	cout << "Counting time: " << setprecision(4) << countingTimeParallel << " seconds" << endl << endl;

	cout << "Sequential method" << endl;
	double startTimeSequential = clock();
	double resultSequential = CalculatePiSequential(size_t(argv[1]));
	cout << "The number Pi: " << resultSequential << endl;
	double endTimeSequential = clock();
	double countingTimeSequential = endTimeSequential - startTimeSequential;
	cout << "Counting time: " << countingTimeSequential / CLOCKS_PER_SEC << " seconds" << endl;

	return 0;
}