#pragma once

class Merge
{
private:
	std::vector <int> FillArray(std::string fileName);
	void mergeProcess(std::vector<int> &vec, int primary, int middle, int last);
	void MergeSorting(std::vector<int> &vec, int primary, int last);
	std::vector<int> v;
	std::vector<int> vec;
};