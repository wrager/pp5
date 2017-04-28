#pragma once
#include "stdafx.h" 

class CGammaCoding
{
public:
	void StartProgram(std::string const & fileName, std::string threadNumbers);
	void Parall(size_t start, size_t finish);
private:
	void LoadText(std::ifstream & inputFile);
	void ClearThreadVector(std::vector<std::thread> & thrs, size_t threads);
	void DivideOnThreads();
	void LoadAlphabet();
	void WriteAnswer(std::ofstream & outputFile);

	size_t maxThread;
	std::vector < size_t> alphabet;
	std::vector<std::string> m_text;
};
