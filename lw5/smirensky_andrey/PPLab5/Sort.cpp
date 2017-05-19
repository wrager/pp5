#include "stdafx.h"
#include "Sort.h"


SortArray::SortArray(std::vector<std::vector<int>> & vec, std::string & type)
{
	if (type == "par")
		result = SortParallel(vec);
	else
		result = Sort(vec);
}

std::vector<int> SortArray::Merge(std::vector<int> const& vector1, std::vector<int> const& vector2)
{
	std::vector<int> resultVec;

	std::vector<int> vec1 = vector1;
	std::vector<int> vec2 = vector2;

	while (!vec1.empty() && !vec2.empty())
	{
		if (vec1[0] > vec2[0])
		{
			resultVec.push_back(vec2[0]);
			vec2.erase(vec2.begin());
		}
		else
		{
			resultVec.push_back(vec1[0]);
			vec1.erase(vec1.begin());
		}
	}
	while (!vec1.empty())
	{
		resultVec.push_back(vec1[0]);
		vec1.erase(vec1.begin());
	}
	while (!vec2.empty())
	{
		resultVec.push_back(vec2[0]);
		vec2.erase(vec2.begin());
	}
	return resultVec;
}

std::vector<int> SortArray::Sort(std::vector<std::vector<int>> const & vec)
{
	auto vector = vec;

	while (vector.size() > 1)
	{
		std::vector<std::vector<int>> tempVec;

		for (int i = 0; i < int(vector.size()); i += 2)
		{
			std::vector<std::vector<int>> result;
			if (i + 1 >= vector.size())
			{
				result.push_back(vector[i]);
			}
			else
			{
				result.push_back(Merge(vector[i], vector[i + 1]));
			}

			for (auto & value : result)
			{
				tempVec.push_back(value);
			}
		}
		vector = tempVec;
	}
	return vector[0];
}

std::vector<int> SortArray::SortParallel(std::vector<std::vector<int>> const & vec)
{
	auto vector = vec;

	while (vector.size() > 1)
	{
		std::vector<std::vector<int>> tempVec;

#pragma omp parallel for
		for (int i = 0; i < int(vector.size()); i += 2)
		{
			std::vector<std::vector<int>> result;
			if (i + 1 >= vector.size())
			{
				result.push_back(vector[i]);
			}
			else
			{
				result.push_back(Merge(vector[i], vector[i + 1]));
			}

#pragma omp critical
			for (auto & value : result)
			{
				tempVec.push_back(value);
			}
		}
		vector = tempVec;
	}
	return vector[0];
}