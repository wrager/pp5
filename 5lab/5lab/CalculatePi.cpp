#include "stdafx.h"
#include <stdio.h>
#include "CalculatePi.h"

using namespace std;

CalculatePi::CalculatePi()
{
}

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

//TODO Parallel


