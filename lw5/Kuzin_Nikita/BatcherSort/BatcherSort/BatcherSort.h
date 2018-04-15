#pragma once
#include <thread>
#include <mutex>

class CBatcherSort
{
public:
	CBatcherSort(std::string inputFilename, std::string outputFilename);
	void Execute();
private:
	std::vector<int> ReadStart();
	void WriteResult(std::vector<int> result);

	void BatcherSort(std::vector<int> & source);

	void OddEvenMergeSort(int lo, int n);

	void OddEvenMerge(int lo, int n, int r);

	void Compare(int i, int j);

	std::vector<int> m_startVec;

	std::string m_input;
	std::string m_output;
};

