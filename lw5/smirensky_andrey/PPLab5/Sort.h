#pragma once
#include "stdafx.h"

class SortArray
{
public:
	SortArray(std::vector<std::vector<int>> & vec, std::string & type);

	std::vector<int> Merge(std::vector<int> const& vector1, std::vector<int> const& vector2);

	std::vector<int> Sort(std::vector<std::vector<int>> const & vec);
	std::vector<int> SortParallel(std::vector<std::vector<int>> const & vec);

private:
	std::vector<int> result;
};
