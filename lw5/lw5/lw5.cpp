#include "stdafx.h"
#include "MonteCarloPiCalculator.h"

using namespace std;

int main(int argc, char *argv[])
{
	int iterNum = 1000000;

	srand(time(NULL));
	cout << CMonteCarloPiCalculator::GetPi(iterNum) << endl;
	getchar();

    return SUCCESS;
}