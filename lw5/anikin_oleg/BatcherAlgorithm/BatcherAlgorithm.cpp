// BatcherAlgorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CalculatorAgregator.h"
#include "BatcherBaseCalculator.h"
#include <sstream>

int main()
{
    CBatcherBaseCalculator calc;
    CCalculatorAggregator aggregator(calc, "fil.txt");
    aggregator.Start();
    return 0;
}

