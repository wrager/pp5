#pragma once
#include <thread>
#include <mutex>

class CBatcherSort
{
public:
	enum class SortType { SIMPLE_MERGE, BATCHER };
	CBatcherSort(std::string inputFilename, std::string outputFilename);
	void Execute(SortType type);
private:
	static std::vector<int> MergeVectors(std::vector<int> vec1, std::vector<int> vec2);
	std::vector<int> ReadStart();
	void WriteResult(std::vector<int> result);

	std::vector<int> SimpleMergeSort(std::vector<int> & source);

	void ProcessStep(std::mutex & mutex, std::vector<std::vector<int>> splitedStart, std::vector<std::vector<int>> & temp);

	void BatcherSort(std::vector<int> & source);

	void OddEvenMergeSort(int lo, int n);

	void OddEvenMerge(int lo, int n, int r);

	void Compare(int i, int j);

	std::vector<int> m_startVec;
	std::string m_input;
	std::string m_output;

	std::vector<std::thread> m_simpleThreadPool;
};

