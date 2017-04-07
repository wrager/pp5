// SimpleMergeSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SimpleMergeSort.h"

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		std::cout << "Hint: input.txt output.txt" << std::endl;
		return -1;
	}

	CSimpleMergeSort simpleMerge(argv[1], argv[2]);
	simpleMerge.Execute();

	return 0;
}

