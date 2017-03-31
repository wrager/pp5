#include "MergeSorter.h"
#include "ParallelMergeSorter.h"
#include "ParallelShellSorter.h"
#include <iostream>
#include <fstream>
#include "DataReader.h"
#include "DataWriter.h"
#include "Utils.h"


int main()
{
	//ReadingData
	std::vector<int> data = DataReader::ReadFromFile();

	//MergeSort
	std::cout << "MergeSort:\nsimple time: ";
	CMergeSorter simpleMergeSorter(data);
	CUtils::CalculateFunctionTime([&]() {simpleMergeSorter.Sort(data); });

	std::cout << "threaded time:";
	CParallelMergeSorter threadedMergeSorter(data);
	CUtils::CalculateFunctionTime([&]() {threadedMergeSorter.Sort(data); });

	//ShellSort
	std::cout << "\nShellSort:\nsimple time: ";
	CShellSorter shellSorter(data);
	CUtils::CalculateFunctionTime([&]() {shellSorter.Sort(); });

	std::cout << "threaded time:";
	CParallelShellSorter parallelShellSorter(data);
	CUtils::CalculateFunctionTime([&]() {parallelShellSorter.Sort(); });

	//WritingResulToFile
	DataWriter::WriteToFile(parallelShellSorter.GetData());

	return 0;
}