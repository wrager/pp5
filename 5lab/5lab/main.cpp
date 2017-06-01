#include "stdafx.h"
#include "CalculatePi.h"

using namespace std;



int main(int argc, char** argv)
{
	cout << "Sequential" << endl;
	float startTimeSequential = clock();
	float resultSequential = CalculatePiSequential(size_t(argv[1]));
	cout << "Pi: " << resultSequential << endl;
	float endTimeSequential = clock();
	float countingTimeSequential = endTimeSequential - startTimeSequential;
	cout << "Time: " << countingTimeSequential / CLOCKS_PER_SEC << " seconds" << endl;

	//TODO Parallel

	return 0;
}


