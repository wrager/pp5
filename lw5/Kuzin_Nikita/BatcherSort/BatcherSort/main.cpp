// Lab5MergeSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BatcherSort.h"

int main(int argc, char * argv[])
{
	if (argc != 4)
	{
		std::cout << "Hint: input.txt output.txt [simple_merge | batcher]" << std::endl;
		return -1;
	}

	CBatcherSort batcherSort(argv[1], argv[2]);
	std::string sortingType = argv[3];
	if (sortingType == "simple_merge")
	{
		batcherSort.Execute(CBatcherSort::SortType::SIMPLE_MERGE);
	}
	else if (sortingType == "batcher")
	{
		batcherSort.Execute(CBatcherSort::SortType::BATCHER);
	}

    return 0;
}