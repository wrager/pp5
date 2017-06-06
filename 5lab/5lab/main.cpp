#include "stdafx.h"
#include "CalculatePi.h"

using namespace std;



int main(int argc, char** argv)
{
	size_t input;
	cout << "enter data: ";
	cin >> input;

	cout << "Sequential" << endl;
	
	float startTimeSequential = clock();
	float resultSequential = CalculatePiSequential(input);
	cout << "Pi: " << resultSequential << endl;
	float endTimeSequential = clock();
	float countingTimeSequential = endTimeSequential - startTimeSequential;
	cout << "Time: " << countingTimeSequential / CLOCKS_PER_SEC << " seconds" << endl<<endl;

	cout << "Parallel" << endl;

	auto startTimeParallel = omp_get_wtime();
	auto resultParallel = CalculatePiParall(input);
	cout << "Pi: " << resultParallel << endl;
	auto endTimeParallel = omp_get_wtime();
	auto countingTimeParallel = endTimeParallel - startTimeParallel;
	cout << "Time: " << setprecision(4) << countingTimeParallel << " seconds" << endl << endl;

	return 0;
}


