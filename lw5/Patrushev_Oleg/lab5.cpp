#include "stdafx.h"
#include "CalculateAlgorithm.h"

template <typename T>
void OutVector(const std::vector<T>& vec)
{
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<T>(std::cout, " "));
	std::cout << std::endl;
}

int main()
{
	std::vector<int> vec = { 4, 6, 2, 7, 9, 3, 3, 6, 6, 3, 7, 8, 3, 5, 1, 8 };

	OutVector(vec);

	BatchersMergeSorter<int> sorter;
	sorter.Sort(vec);

	OutVector(sorter.GetResultVector());

	return 0;
}
