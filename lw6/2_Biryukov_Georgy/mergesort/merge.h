#pragma once
#include "stdafx.h"

class Merge
{
public:
	std::vector <int> FillArray(std::string fileName);
	void mergeProcess(std::vector<int> &vec, int l, int m, int r);
	void MergeSorting(std::vector<int> &vec, int l, int r);

private:
/*	std::vector<int> v;
//	std::vector<int> vec;
	std::vector<int> filledArray;*/
};
