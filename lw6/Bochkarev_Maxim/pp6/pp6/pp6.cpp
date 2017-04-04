#include "stdafx.h"
#include <sstream>
#include "MonteCarloPiCalculator.h"
#include "ParallelMonteCarloPiCalculator.h"
#include <chrono>

using namespace std;

bool ReadCommandLineParameters(int argc, char *argv[], int& clientsCount);

int main(int argc, char *argv[])
{
	int iterNum = 0;

	if (!ReadCommandLineParameters(argc, argv, iterNum))
	{
		cout << "Command line parameters read error. Run app with /? to help.\n";
		getchar();
		return ERR;
	}
	auto t1 = chrono::high_resolution_clock::now();
	cout << "Programm started Monte Carlo Pi Calculation with " << iterNum << " iterations.\n";
	cout << CMonteCarloPiCalculator::GetPi(iterNum) << endl;
	auto t2 = chrono::high_resolution_clock::now();
	cout << "Process took: " << chrono::duration_cast< chrono::milliseconds>(t2 - t1).count() << " milliseconds\n\n\n";

	t1 = chrono::high_resolution_clock::now();
	cout << "Programm started parallel Monte Carlo Pi Calculation with " << iterNum << " iterations.\n";
	cout << ParallelMonteCarloPiCalculator::GetPi(iterNum) << endl;
	t2 = chrono::high_resolution_clock::now();
	cout << "Process took: " << chrono::duration_cast< chrono::milliseconds>(t2 - t1).count() << " milliseconds\n";

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
		if(!(ss >> iterNum))
		{
			cout << "Command line parse error, check your input!\n";
			return false;
		}
		return true;
	}
	return true;
}