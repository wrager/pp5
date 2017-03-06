#include "stdafx.h"
#include <omp.h>

void PushLastElems(std::vector<int> & v1, std::vector<int> & v2)
{
	while (v1.size() > 0)
	{
		v2.push_back(v1[0]);
		v1.erase(v1.begin());
	}
}

void WriteVec(std::vector<int> vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}

std::vector<int> MakeNewVector(std::vector<int> vec1, std::vector<int> vec2)
{
	int size = vec1.size() + vec2.size();
	std::vector<int> vec3;
	while (vec1.size() > 0 && vec2.size() > 0)
	{
		int first = vec1[0];
		int second = vec2[0];
		if (first > second)
		{
			vec3.push_back(second);
			vec2.erase(vec2.begin());
		}
		else
		{
			vec3.push_back(first);
			vec1.erase(vec1.begin());
		}
	}
	PushLastElems(vec1, vec3);
	PushLastElems(vec2, vec3);
	return vec3;
}

std::vector<int> MergeSort(std::vector<int> & vec)
{
	std::vector<int> vec1;
	std::vector<int> vec2;
	if (vec.size() > 0)
	{
		if (vec.size() > 2)
		{
			vec1.resize(vec.size() / 2);
			vec2.resize(vec.size() - vec.size() / 2);
			std::copy(vec.begin(), vec.begin() + vec.size() / 2, vec1.begin());
			std::copy(vec.begin() + vec.size() / 2, vec.end(), vec2.begin());
#pragma omp parallel num_threads(2)
#pragma omp for
			for (int i = 0; i < 2; i++)
			{
				if (i == 0)
				{
					vec1 = MergeSort(vec1);

				}
				else
				{
					vec2 = MergeSort(vec2);

				}
			}
		}
		else
		{
			if (vec.size() != 1)
			{
				if (vec[0] > vec[1])
				{
					std::swap(vec[0], vec[1]);
				}
			}
			return vec;
		}

		return MakeNewVector(vec1, vec2);
	}
	return vec;
}

int main(int argc, char **argv)
{
	srand(time(0));
	size_t size = 100000;
	std::cout << "size of array = " << size << std::endl;
	std::vector<int>vec(size);
	const int threads = 10;
#pragma omp parallel num_threads(threads)
#pragma omp for schedule(dynamic, size / threads)
	for (int i = 0; i < size; i++)
	{
		vec[i] = rand() % 100;
	}
	std::vector<int> vec3;

	vec3 = MergeSort(vec);
	std::cout << "runtime = " << clock() / 1000.0 << std::endl;
	return 0;
}