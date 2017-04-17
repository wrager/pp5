#pragma once

#include <vector>
#include <string>
#include <Windows.h>
#include <ctime>
#include <string>
#include <iostream>

class CTaskSolver
{
public:
	CTaskSolver();
	~CTaskSolver();
//////////////////////////////////////////////////////////////////////
// Methods
public:
	double							GetPi(size_t amountIteration, size_t amountThreads);
private:

	std::string						GetMessageForThread(
															size_t amountIteration
															, double result
															, int indexThread
														);
//////////////////////////////////////////////////////////////////////
// Static Methods
private:
	static size_t					CalculateHits(size_t numIter);

	static double					RandomNumber();
	static bool						InCircle(double x, double y);
//////////////////////////////////////////////////////////////////////
// Data
private:
	size_t							m_numberProcess;
	size_t							m_amountIterations;
};

