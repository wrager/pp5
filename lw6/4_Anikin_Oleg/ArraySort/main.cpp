#include "stdafx.h"
#include "SorterFactory.h"
#include "SortTypes.h"

using namespace sorts;

int main()
{
    std::unique_ptr<ISorterFactory> factory = std::make_unique<CSorterFactory>();
    auto sorter = factory->CreateParallelSorter(SortTypes::Merge);
    auto result = sorter->GetSortedResult({ 2,1,3,4,5,6 });

    return 0;
}

