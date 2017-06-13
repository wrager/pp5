#pragma once

class CThreadWrapper;

class CApplication
{
public:
	CApplication() = default;
	CApplication(CIOManager *manager);
	void SetInputFileName(std::string const &name);
	void SetOutputFileName(std::string const &name);
	void ProcessFile();
	bool EditNextFragment();
	void OutputResultsInFile();
	void ThreadFunction();
	~CApplication();
private:
	void SaveNewInformation(CCompressor &compressor);
	void Wait() const;
private:
	CRepositoryProcessedData m_myRepository;
	CIOManager *m_iomanager = nullptr;
	std::mutex m_mutex;
	std::mutex m_mutexForCompressor;
	int m_nextThreadOrderForWrite;
	std::vector<CThreadWrapper*> m_threads;
};