#include "stdafx.h"
#include "MergeArraySorter.h"
#include "ShellArraySorter.h"
#include "Utils.h"
#include <map>

static const std::map<std::string, bool> STR_BOOL_COLLECTION = {
	{"true", true},
	{"false", false}
};

template <typename SorterType>
ArraySorterPtr StartSort(const SortableArray &arrayForSort, bool isParallel)
{
	auto sorter = SorterType::CreateSorter(arrayForSort, isParallel);
	const auto elapsedTime = utils::NotifyExecutionTime([&]() {
		sorter->Sort();
	});
	std::cout << "Elapsed time: " << elapsedTime << "\n";
	return sorter;
}

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		std::cout << "Invalid arguments count" << std::endl;
		return EXIT_FAILURE;
	}

	try
	{
		const auto isParallel = STR_BOOL_COLLECTION.at(argv[2]);
		const auto vecForSorting = utils::ReadVectorFromFile(argv[1]);

		std::cout << "Merge Sort with paralleling enabled: " << argv[2] << "\n";
		StartSort<CMergeArraySorter>(vecForSorting, isParallel);

		std::cout << "Shell Sort with paralleling enabled: " << argv[2] << "\n";
		StartSort<CShellArraySorter>(vecForSorting, isParallel);
	}
	catch (const std::exception &except)
	{
		std::cout << except.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch (...)
	{
		std::cout << "Unknown exception" << std::endl;
		return EXIT_FAILURE;
	}

    return EXIT_SUCCESS;
}

