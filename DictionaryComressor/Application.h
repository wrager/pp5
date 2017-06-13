#pragma once

class CCustomThread;

class CAppManager
{
public:
	CAppManager() = default;
	CAppManager(CIOHandler * manager);
	
	void SetInputFileName(std::string const &name);
	void SetOutputFileName(std::string const &name);
	void ProcessFile();
	void SaveResult();
	void CompressFragment();

	~CAppManager();
private:
	void SetNewTextFragment(CCompressor &compressor);

	CRepository m_repository;
	CIOHandler *m_iohandler = nullptr;
	std::mutex m_mutex;
	std::mutex m_compressorMutex;
	int m_nextNumberThreadForWrite;
	std::vector<std::thread*> m_mthreads;
};