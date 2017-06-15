#pragma once
#include <thread>
#include <mutex>

class CSimpleMergeSort
{
public:
	CSimpleMergeSort(std::string inputFilename, std::string outputFilename);
	void Execute();
private:
	static std::vector<int> MergeVectors(std::vector<int> vec1, std::vector<int> vec2);
	std::vector<int> ReadStart();
	void WriteResult(std::vector<int> result);

	std::vector<int> SimpleMergeSort(std::vector<int> & source);

	std::string m_input;
	std::string m_output;

	std::vector<std::thread> m_simpleThreadPool;
};

