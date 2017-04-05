#pragma once

class CApplication
{
public:
	CApplication() = default;
	CApplication(CIOManager *manager);
	void SetInputFileName(std::string const &name);
	void SetOutputFileName(std::string const &name);
	void ProcessFile();
	bool EditNextFragment();
	~CApplication();
private:
	void SaveNewInformation(CCompressor &compressor);
	void OutputResultsInFile();
private:
	CMyRepository m_myRepository;
	CIOManager *m_iomanager = nullptr;
	std::mutex m_mutex;
	int m_nextThreadOrderForWrite;
};