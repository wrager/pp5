#pragma once
#include <time.h>

template <class T>
double GetCalculatedTime(T && callback)
{
	double beginTime = clock();
	callback();
	double finishTime = clock();
	return double((finishTime - beginTime) / 1000.0);
};