#include "stdafx.h"
#include "MonteCarloPiCalculator.h"
#include <sstream>

using namespace std;

bool ReadCommandLineParameters(int argc, char *argv[], int& clientsCount);

int main(int argc, char *argv[])
{
	int iterNum = 0;

	if (!ReadCommandLineParameters(argc, argv, iterNum))
	{
		cout << "Command line parameters read error. Run app with /? to help.\n";
		return ERR;
	}

	srand(time(NULL));

	double start, end, calculationTime;
	start = omp_get_wtime();

	cout << "Programm started Monte Carlo Pi Calculation with " << iterNum << " iterations.\n";
	cout << CMonteCarloPiCalculator::GetPi(iterNum) << endl;

	end = omp_get_wtime();
	calculationTime = end - start;
	cout << "Calculation Time: " << calculationTime << "\n";

	return SUCCESS;
}

bool ReadCommandLineParameters(int argc, char *argv[], int& iterNum)
{
	if (argc != 2)
	{
		cout << "Incorrect amount of parameters. Use /? for help. " << endl;
		return false;
	}
	else
	{
		istringstream ss(argv[1]);
		if (!(ss >> iterNum))
		{
			cout << "Command line parse error, check your input!\n";
			return false;
		}
		return true;
	}
	return true;
}