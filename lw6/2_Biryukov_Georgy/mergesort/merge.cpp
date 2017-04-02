// MergeSorting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "merge.h"

using namespace std;

std::vector<int> Merge::FillArray(std::string fileName)
{
	std::vector <int> filledArray;
	ifstream file(fileName);
	int i;

	while (!file.eof())
	{
		file >> i;
		filledArray.push_back(i);
	}
	return filledArray;
}

void Merge::mergeProcess(std::vector<int>& vec, int l, int m, int r)
{
	int i = l;
	int j = m + 1;
	std::vector<int> temp;

	while (i <= m && j <= r) {
		if (vec.at(i) <= vec.at(j)) {
			temp.push_back(vec.at(i++));
		}
		else {
			temp.push_back(vec.at(j++));
		}
	}
	while (i <= m) {
		temp.push_back(vec.at(i++));
	}
	while (j <= r) {
		temp.push_back(vec.at(j++));
	}
	std::copy(temp.begin(), temp.end(), vec.begin() + l);
}

void MergeSorting(std::vector<int>& vec, int l, int r)
{
	Merge merge;
	if (l < r) {
		int m = (l + r) / 2;
		std::thread sort_thread1([&vec, l, m] { MergeSorting(vec, l, m);});
		std::thread sort_thread2([&vec, m, r] { MergeSorting(vec, m + 1, r); });
		sort_thread1.join();
		sort_thread2.join();
		merge.mergeProcess(vec, l, m, r);
	}
}

int main(int argc, char *argv[])
{
	Merge merge;

	if (argc > 1)
	{
		std::vector<int> v = merge.FillArray(std::string(argv[1]));
		clock_t time = clock();
		MergeSorting(v, 0, (v.size() - 1));
		time = clock();
		std::cout << "Manipulation time " << ((float)time) / CLOCKS_PER_SEC << " sec" << std::endl;

		for (const int &a : v) {
			std::cout << a << " ";
		}

		std::cout << std::endl;
	}
	else
	{
		std::cout << "not enough arguments. Example: mergesort.exe FileName.txt" << std::endl;
	}
	return 0;
}

