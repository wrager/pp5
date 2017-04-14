// Lab5MergeSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

std::vector<int> MergeVectors(std::vector<int> const& vec1, std::vector<int> const& vec2)
{
	std::vector<int> resultVec;
	auto v1 = vec1;
	auto v2 = vec2;
	std::reverse(v1.begin(), v1.end());
	std::reverse(v2.begin(), v2.end());
		for (; !v1.empty() && !v2.empty();)
		{
			if (v1.back() > v2.back())
			{
				resultVec.push_back(v2.back());
				v2.pop_back();
			}
			else
			{
				resultVec.push_back(v1.back());
				v1.pop_back();
			}
		}
	while (!v1.empty())
	{
		resultVec.push_back(v1.back());
		v1.pop_back();
	}
	while (!v2.empty())
	{
		resultVec.push_back(v2.back());
		v2.pop_back();
	}
	return resultVec;
}

std::vector<int> MergeSort(std::vector<std::vector<int>> const& vec)
{
	auto sndVec = vec;
	while (sndVec.size() > 1)
	{
		std::vector<std::vector<int>> tempSnd;
#pragma omp parallel for
		for (int i = 0; i < int(sndVec.size()); i += 2)
		{
			std::vector<std::vector<int>> result;
			if (i + 1 >= sndVec.size())
			{
				result.push_back(sndVec[i]);
			}
			else if (i + 1 < sndVec.size())
			{
				result.push_back(MergeVectors(sndVec[i], sndVec[i + 1]));
			}
#pragma omp critical
			{
				for (auto &it : result)
				{
					tempSnd.push_back(it);
				}
			}
		}
		sndVec = tempSnd;
	}
	return sndVec[0];
}


int main(int argc, char * argv[])
{

	if (argc < 2)
		return 1;
	std::ifstream input(argv[1]);

	std::vector<int> numVec;

	for (; !input.eof();)
	{
		int num;
		input >> num;
		numVec.push_back(num);
	}

	std::vector<std::vector<int>> myVec;
	for (auto &elem : numVec)
	{
		myVec.push_back(std::vector<int>());
		myVec.back().push_back(elem);
	}
	auto start = std::chrono::system_clock::now();
	auto result = MergeSort(myVec);
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> dif = end - start;
	std::cout << "Time " << dif.count() << std::endl;
    return 0;
}

