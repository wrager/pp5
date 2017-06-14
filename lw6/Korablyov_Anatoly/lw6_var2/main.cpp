#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <string>

#include "MergeSort.h"

std::vector<unsigned> ReadFile(const std::string & nameFile)
{
	std::ifstream inpFile(nameFile);
	if (!inpFile.is_open())
	{
		std::cout << "File not found!";
		exit(1);
	}

	std::vector<unsigned> vecNum;
	while (!inpFile.eof())
	{
		std::string mainString;
		inpFile >> mainString;
		vecNum.push_back(atoi(mainString.c_str()));
	}

	return vecNum;
}

void WriteToFile(const std::string & nameFile, const std::vector<unsigned> & numArr)
{
	std::ofstream inpFile(nameFile);
	inpFile << "{ ";
	for (auto it : numArr)
	{
		inpFile << it << ", ";
	}
	inpFile << " }";
}

void Measurement(const std::string & inFile, const std::string & outFile, bool parallel)
{
	std::chrono::time_point<std::chrono::system_clock> startTime, endTime;

	startTime = std::chrono::system_clock::now();

	std::vector<unsigned> number = ReadFile(inFile);
	CMergeSort mergeSort;
	std::vector<unsigned> res; mergeSort.MergeSortParallel(number);
	std::string outFileName;
	if (parallel)
	{
		res = mergeSort.MergeSortParallel(number);
		outFileName = "Parallel";
	}
	else
	{
		res = mergeSort.MergeSortSequence(number);
		outFileName = "Sequence";
	}
	WriteToFile(outFileName + outFile.c_str(), res);

	endTime = std::chrono::system_clock::now();
	std::cout << outFileName << " : " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms" << std::endl;
}


int main(int argc, char * argv[])
{
	if (argc == 3)
	{
		std::string inFile = argv[1];
		std::string outFile = argv[2];

		Measurement(inFile, outFile, true);
		Measurement(inFile, outFile, false);
	}
	return 0;
}