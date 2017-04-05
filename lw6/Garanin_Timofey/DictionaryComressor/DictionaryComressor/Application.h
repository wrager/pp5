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
	void OutputResultsInFiles(CCompressor &compressor);
private:
	CIOManager *m_iomanager = nullptr;
};