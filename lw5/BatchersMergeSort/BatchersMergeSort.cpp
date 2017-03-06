// BatchersMergeSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CalculateAlgorithm.h"

void PrintVector(const std::vector<int>& vec)
{
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
}

void CreateFile(const std::string & filename, size_t number)
{
	std::ofstream outFile(filename);
	if (outFile.is_open())
	{
		for (size_t i = 0; i < number; i++)
		{
			auto random = rand() % number * 10;
			outFile << " " << random;
		}
	}
}

std::vector<int> ReadFile(const std::string & filename)
{
	std::vector<int> resultVec;

	std::ifstream inFile(filename);
	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			std::string word;
			inFile >> word;
			resultVec.push_back(std::stoi(word));
		}
	}
	return resultVec;
}

template <typename T>
void OutputWorkTime(T& callback)
{
	std::chrono::time_point<std::chrono::system_clock> startTime, endTime;

	startTime = std::chrono::system_clock::now();
	callback();
	endTime = std::chrono::system_clock::now();

	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() << std::endl;
}

int main()
{
	CreateFile("data/numbers.txt", 65536);
	std::vector<int> vec = ReadFile("data/numbers.txt");
	CCalculateAlgorithm calcLiner(vec);
	CCalculateAlgorithm calcParallel(vec);

	OutputWorkTime([&]() {calcLiner.BatchersMergeSort(0, vec.size(), false); });
	OutputWorkTime([&]() {calcLiner.BatchersMergeSort(0, vec.size(), true); });
    return EXIT_SUCCESS;
}

