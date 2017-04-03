#include "stdafx.h"
#include "MergeSortCalculator.h"

int main()
{
    auto calculator = CMergeSortCalculator({ 2,1,3,4,5,6 });
    calculator.Sort(true);
    auto result = calculator.GetResult();

    return 0;
}

