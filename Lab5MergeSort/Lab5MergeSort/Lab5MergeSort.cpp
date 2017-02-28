// Lab5MergeSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <fstream>
#include <chrono>
#include <iostream>

using namespace std;

vector<int> MergeVectors(vector<int> const& vec1, vector<int> const& vec2)
{
	vector<int> resultVec;
	auto v1 = vec1;
	auto v2 = vec2;
	reverse(v1.begin(), v1.end());
	reverse(v2.begin(), v2.end());

	while (!v1.empty() && !v2.empty())
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

vector<int> MergeSort(vector<vector<int>> const& vec)
{
	auto sndVec = vec;
	vector<vector<int>> fstVec ;
	while (sndVec.size() > 1)
	{
		fstVec = sndVec;
		sndVec.clear();
		for (size_t i = 0; i < fstVec.size();)
		{
			if (i + 1 >= fstVec.size())
			{
				sndVec.push_back(fstVec[i++]);
			}
			else
			{
				sndVec.push_back(MergeVectors(fstVec[i++], fstVec[i++]));
			}
		}
	}
	return sndVec[0];
}

const vector<int> VEC = { 2, 5, 1, 2, 3, 5, 7, -8, 0, -4, 3, 6, 7, 8, -3, 12, 4, 10 };

int main()
{
	vector<vector<int>> myVec;
	for (auto &elem : VEC)
	{
		myVec.push_back(vector<int>());
		myVec.back().push_back(elem);
	}
	auto start = chrono::system_clock::now();
	auto result = MergeSort(myVec);
	auto end = chrono::system_clock::now();

	chrono::duration<double> dif = end - start;
	cout << "Time " << dif.count() << endl;
    return 0;
}

