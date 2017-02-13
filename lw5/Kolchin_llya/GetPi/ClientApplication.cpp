#include "stdafx.h"
#include "ClientApplication.h"

CClientApplication::CClientApplication(size_t numberProcess)
	: m_numberProcess(numberProcess)
{
}

CClientApplication::~CClientApplication()
{
}

double CClientApplication::GetPi(size_t amountIteration)
{
	srand(UINT(m_numberProcess));// TODO : transfer to other place

	double result =  4.0 * CalculateHits(amountIteration) / amountIteration;

	std::string message = GetFinalMessage(amountIteration, result);

	return result;
}

double CClientApplication::RandomNumber()
{
	return double(rand()) / RAND_MAX;
}

bool CClientApplication::InCircle(double x, double y)
{
	return (x*x + y*y) <= 1;
}

size_t CClientApplication::CalculateHits(size_t numIter)
{
	size_t numHits = 0;
	for (size_t index = 0; index < numIter; ++index)
	{
		numHits += InCircle(RandomNumber(), RandomNumber());// TODO : see can it replace to boost function
	}
	return numHits;
}

// Evenly distributes indexes on processors
std::string CClientApplication::GetFinalMessage(size_t amountIteration, double result)
{
	std::string message = "Id process "
		+ std::to_string(m_numberProcess) + "\n"
		+ "Amount iteration = " + std::to_string(amountIteration) + "\n"
		+ "Result = " + std::to_string(result) + "\n";

	return message;
}