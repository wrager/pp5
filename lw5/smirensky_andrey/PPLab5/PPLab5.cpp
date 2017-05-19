#include "stdafx.h"
#include "Sort.h"


int main(int argc, char * argv[])
{

	if (argc < 3)
		return 1;

	std::ifstream inFile(argv[1]);

	std::vector<int> arr;

	while (!inFile.eof())
	{
		int num;
		inFile >> num;
		arr.push_back(num);
	}

	std::vector<std::vector<int>> vectorForSort;
	for (auto & elem : arr)
	{
		vectorForSort.push_back(std::vector<int>());
		vectorForSort.back().push_back(elem);
	}
	std::string type = argv[2];
	auto start = std::chrono::system_clock::now();
	SortArray sortArray(vectorForSort, type);
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> dif = end - start;
	std::cout << "Time: " << dif.count() << std::endl;
	return 0;
}
