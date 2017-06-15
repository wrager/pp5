#pragma once

#include <vector>
#include <string>
#include <Windows.h>
#include <ctime>
#include <string>
#include <iostream>

#include <thread>
#include <future>

class CTaskSolver
{
public:
	CTaskSolver();
	~CTaskSolver();

	struct ThreadResult
	{
		ThreadResult() = default;
		ThreadResult(double result) 
			: result(result)
		{
		};
		double result;
	};
//////////////////////////////////////////////////////////////////////
// Methods
public:
	static double GetPi(size_t amountIteration, size_t amountThreads);
private:
	static void ComputePi(
		size_t threadId,
		size_t amountIteration,
		size_t amountPoints,
		ThreadResult & result
	);

	static std::string GetMessageForThread(
		size_t amountIteration
		, double result
		, size_t indexThread
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

