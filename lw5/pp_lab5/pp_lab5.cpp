// pp_lab5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Utils.h"
#include "BatcherCalculator.h"

bool IsArgumentsCountCorrect(int argsCount)
{
	return argsCount == 3;
}

int main(int argc, char *argv[])
{
	try
	{
		if (!IsArgumentsCountCorrect(argc))
		{
			std::cout << "Args count is incorrect" << std::endl;
			return EXIT_FAILURE;
		}
		std::ifstream fileStrm;
		CUtils::TryToOpenFileStream(fileStrm, argv[1]);
		auto inputVec = CUtils::ReadNumbersFromStrm(fileStrm);

		CBatcherCalculator calc(inputVec);
		bool isParallel = CUtils::StringParallelStatusArgToBool(argv[2]);

		clock_t begin = clock();
		calc.Sort(isParallel);
		clock_t end = clock();

		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		std::cout << "Spent time: " + std::to_string(elapsed_secs) + " with paralleling status: " << argv[2] << std::endl;
#if 0 //preprocessor macros for optional print action; change value to 1 for print numbers array
		CUtils::PrintNumbersArray(calc.GetResultVec());
#endif
	}
	catch (const std::exception &ex)
	{
		std::cerr << ex.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (...)
	{
		std::cerr << "Unknown error" << std::endl;
		return EXIT_FAILURE;
	}
    return EXIT_SUCCESS;
}

