#pragma once
class CBatcherSort
{
public:
	CBatcherSort(std::string inputFilename, std::string outputFilename);
	void Execute();
private:
	static std::vector<int> MergeVectors(std::vector<int> vec1, std::vector<int> vec2);
	std::vector<std::vector<int>> ReadStart();
	void WriteResult(std::vector<int> result);

	std::vector<int> Sort(std::vector<std::vector<int>> & start);
	std::vector<std::vector<int>> m_startVec;
	std::string m_input;
	std::string m_output;
};

