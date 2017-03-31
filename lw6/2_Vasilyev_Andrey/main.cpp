#include "SimpleMergeSorter.h"
#include "ParallelMergeSorter.h"
#include "ParallelShellSorter.h"
#include <iostream>
#include <fstream>
#include "DataReader.h"
#include "DataWriter.h"
#include "Utils.h"
#include "Sorter.h"
#include <memory>
#include <string>
#include <array>
#include <algorithm>

void DoWorkWithSorter(CSorter & sorter)
{
	std::cout << sorter.ToString() << " time:";
	CUtils::CalculateFunctionTime([&]() {sorter.Sort(); });
	std::cout << std::endl;
}

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		std::cout << "Error: incorrect usage. Example: \"lab6.exe input.txt\"" << std::endl;	
		return 1;
	}
	
	std::vector<int> data;
	try
	{
		data = DataReader::ReadFromFile(argv[1]);
	}
	catch (const std::ios_base::failure & ex)
	{
		std::cout << "Error: " << ex.what() << std::endl;
		return 2;
	}
	 

	std::unique_ptr<CSorter> sorters[] =
	{
			std::make_unique<CSimpleMergeSorter>(data),
			std::make_unique<CParallelMergeSorter>(data),
			std::make_unique<CSimpleShellSorter>(data),
			std::make_unique<CParallelShellSorter>(data)
	};

	std::cout << "Data loaded successfully, checking calculation time..." << std::endl;

	for(size_t i = 0; i < 4; ++i)
	{
		DoWorkWithSorter(*(sorters[i].get()));
	};

	DataWriter::WriteToFile(sorters[0]->GetData());

	return 0;
}