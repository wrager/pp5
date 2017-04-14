#include "stdafx.h"
#include "MergeSortCalculator.h"
#include "ShellSortCalculator.h"
#include "CalculatorAgregator.h"

int main()
{
    try
    {
        std::cout << "Merge:" << "\n";
        CMergeSortCalculator mergeCalc;
        CCalculatorAggregator mergeAggregator(mergeCalc, "fil.txt");
        mergeAggregator.Start();

        std::cout << "Shell:" << "\n";
        CShellSortCalculator shellCalc;
        CCalculatorAggregator shellAggregator(shellCalc, "fil.txt");
        shellAggregator.Start();
    }
    catch (const std::exception & except)
    {
        std::cout << except.what() << std::endl;
        return 1;
    }

    return 0;
}
