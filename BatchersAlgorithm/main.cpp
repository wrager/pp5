#include <iostream>
#include <vector>
#include <string>
#include "CSorter.h"
#include "CUtils.h"


int main()
{
	std::vector<int> vec = CUtils::InitializeVector(1024);
	COddEvenMergeSorter sorter(vec);
	sorter.Sort();

	return 0;
}