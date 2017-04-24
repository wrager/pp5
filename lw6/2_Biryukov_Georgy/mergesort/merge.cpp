#include "stdafx.h"
#include "arraymanager.cpp"
#include "merge.h"

using namespace std;

void Merge::MergeProcess(std::vector<int>& vec, int primary, int middle, int last)
{
	int i = primary;
	int j = middle + 1;
	std::vector<int> temp;

	while (i <= middle && j <= last) {
		if (vec.at(i) <= vec.at(j)) {
			temp.push_back(vec.at(i++));
		}
		else {
			temp.push_back(vec.at(j++));
		}
	}
	while (i <= middle) {
		temp.push_back(vec.at(i++));
	}
	while (j <= last) {
		temp.push_back(vec.at(j++));
	}
	std::copy(temp.begin(), temp.end(), vec.begin() + primary);
}

void Merge::MergeSorting(std::vector<int>& vec, int primary, int last)
{
	Merge merge;
	if (primary < last) {
		int middle = (primary + last) / 2;
		std::thread sort_thread1([&vec, primary, middle] { merge.MergeSorting(vec, primary, middle);});
		sort_thread1.join();
		std::thread sort_thread2([&vec, middle, last] { merge.MergeSorting(vec, middle + 1, last); });
		sort_thread2.join();
		merge.MergeProcess(vec, primary, middle, last);
	}
}