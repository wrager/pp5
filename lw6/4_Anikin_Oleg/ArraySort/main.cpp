#include "stdafx.h"
#include "MergeSortCalculator.h"
#include "CalculatorAgregator.h"

int main()
{
    CMergeSortCalculator calc;
    CCalculatorAggregator aggregator(calc, "fil.txt");
    aggregator.Start();
    return 0;
}
