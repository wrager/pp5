#include "SorterFactory.h"


std::unique_ptr<CSorter> CSorterFactory::CreateSorter(CSorter::Type type, bool isParallel)
{
	switch (type)
	{
	case CSorter::MERGE:
		return isParallel ? std::make_unique<CParallelMergeSorter>() : std::make_unique<CSimpleMergeSorter>();
	case CSorter::SHELL:
		return isParallel ? std::make_unique<CParallelShellSorter>() : std::make_unique<CSimpleShellSorter>();
	}
	throw std::logic_error("Invalid sorter type.");
}