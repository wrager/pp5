#include "stdafx.h"
#include "LinearSorter.h"
#include "ThreadedSorter.h"

template <typename T>
void OutVector(const std::vector<T>& vec)
{
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(std::cout, " "));
	std::cout << std::endl;
}

std::vector<int> ConvertVecStringToInt(const std::vector<std::string>& vec)
{
	std::vector<int> intVec;
	for (auto element : vec)
	{
		intVec.push_back(std::stoi(element));
	}

	return intVec;
}

template <typename T>
std::vector<T> ReadDataFromFile(const std::string& filename)
{
	std::vector<T> resultVec;

	std::ifstream inFile(filename);
	for (std::string line; std::getline(inFile, line);)
	{
		std::stringstream stream(line);
		std::vector<std::string> splittedString
		{
			std::istream_iterator<std::string>(stream),{}
		};
		auto intVec = ConvertVecStringToInt(splittedString);
		resultVec.insert(resultVec.end(), intVec.begin(), intVec.end());
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


	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << std::endl;
}

int main()
{
	std::vector<int> vec = ReadDataFromFile<int>("numbers.txt");
	
	CBatchersMergeSorterLinear<int> sorterLinear = CBatchersMergeSorterLinear<int>(vec);
	CBatchersMergeSorterParallel<int> sorterParallel = CBatchersMergeSorterParallel<int>(vec);

	OutputWorkTime([&]() {sorterLinear.Sort();});
	
	OutputWorkTime([&]() {sorterParallel.Sort();});

	return 0;
}
