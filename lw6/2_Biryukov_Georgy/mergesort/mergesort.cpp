#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm> // подключаем заголовок с алгоритмами STL
#include <functional>
#include <vector>

using namespace std;

bool SortIterator(int a, int b) 
{
	return (a > b);
}

std::vector <int> FillArray(std::string fileName)
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

std::vector <int> SeparateArray(std::vector <int> filledArray, size_t tapeIndex)
{
	std::vector <int> separatedArray;
	size_t i;

	for (i = tapeIndex; i < filledArray.size(); i+= 2) {
		separatedArray.push_back(filledArray[i]);
	}

	return separatedArray;
}

std::vector <int> SortProcess(std::vector <int> array) 
{
	sort(array.begin(), array.end(), SortIterator);
	return array;
}

std::vector <int> MergeArray(std::vector <int> array1, std::vector <int> array2)
{
	std::vector <int> mergedArray;
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;

	while (k != (array1.size() + array2.size()) - 1)
	{
		if (array1[i] >= array2[j]) 
		{
			mergedArray.push_back(array1[i]);
			i++;
		}
		else
		{
			mergedArray.push_back(array2[j]);
			j++;
		}
		k++;
	}

	if (array1.size() > array2.size())
	{
		mergedArray.push_back(array1.back());
	}
	else
	{
		mergedArray.push_back(array2.back());
	}

	return mergedArray;
}

int main(int argc, char *argv[])
{
	if (argc > 1) 
	{ 
		std::vector <int> merged = MergeArray(SortProcess(SeparateArray(FillArray(std::string(argv[1])), 0)), SortProcess(SeparateArray(FillArray(std::string(argv[1])), 1)));
		int j;
		for (j = 0; j < merged.size(); j++) {
			std::cout << merged[j] << " ";
		}
	}
	else
	{
		std::cout << "not enough arguments. Example: mergesort.exe FileName.txt" << std::endl;
	}
	return 0;
}