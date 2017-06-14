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
#include "SorterFactory.h"
#include <vector>

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
	
	std::vector<std::unique_ptr<CSorter>> sorters;
	sorters.push_back(CSorterFactory::CreateSorter(CSorter::MERGE, false));
	sorters.push_back(CSorterFactory::CreateSorter(CSorter::MERGE, true));
	sorters.push_back(CSorterFactory::CreateSorter(CSorter::SHELL, false));
	sorters.push_back(CSorterFactory::CreateSorter(CSorter::SHELL, true));

	for(auto & el : sorters)
	{
		el->SetData(data);
		DoWorkWithSorter(*el);
	};

	DataWriter::WriteToFile(sorters[0]->GetData());

	return 0;
}