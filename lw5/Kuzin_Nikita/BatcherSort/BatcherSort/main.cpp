// Lab5MergeSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BatcherSort.h"

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		std::cout << "Hint: input.txt output.txt" << std::endl;
		return -1;
	}

	CBatcherSort batcherSort(argv[1], argv[2]);
	batcherSort.Execute();

    return 0;
}