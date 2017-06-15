#pragma once
#include "AsyncManager.h"
#include <vector>

class Sorter
{
public:
	Sorter(AsyncManager  & manager);
	~Sorter();

	void SetArray(std::vector<int> const& array);
	void StartSort();

	void SetThreadCount(int count);
private:

	static void SortVec(std::vector<std::vector<int>> &vec, std::vector<std::vector<int>>& resultVec, std::mutex* vecMute);
	static void MergeVectors(std::vector<int> const& vec1, std::vector<int> const& vec2, std::vector<std::vector<int>> & mainVec, std::mutex * mutex);

	std::vector<std::vector<int>> m_elements;

	AsyncManager & m_manager;

	int m_threadCount;
};

