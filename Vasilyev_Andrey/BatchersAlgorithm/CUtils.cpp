#include "CUtils.h"

std::vector<int> CUtils::InitializeVector(size_t nElems)
{
	std::vector<int> result;
	for (size_t i = nElems; i > 0; --i)
	{
		result.push_back(i);
	}
	return result;
}