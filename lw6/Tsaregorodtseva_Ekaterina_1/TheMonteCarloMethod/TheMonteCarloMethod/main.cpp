// TheMonteCarloMethod.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "LinearPi.h"
#include "ParallelPi.h"

using namespace std;

long int CharToLongInt(char* elem)
{
	stringstream strm;
	strm << elem;
	long int result;
	strm >> result;
	return result;
}

int main(int argc, char* argv[])
{
	long int numbIteration = CharToLongInt(argv[1]);
	
	CLinearPi linPi;
	linPi.Calculate(numbIteration);
	cout << "Pi = " << linPi.Get() << endl;

	CParallelPi paralPi;
	paralPi.Calculate(numbIteration);
	cout << "Pi = " << paralPi.Get() << endl;
	
}