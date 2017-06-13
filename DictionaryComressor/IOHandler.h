#pragma once

class CIOHandler
{
public:
	CIOHandler(std::string const &inFile, std::string const &outFile);
	CIOHandler();
	int GetOrder() const;
	bool IsFileRead() const;
	void PrepareEnvironment();
	char* GetViewMappingFile();
	size_t GetSizeView() const;
	void SetInputFileName(std::string const &name);
	void SetOutputFileName(std::string const &name);
	void OutputDictionary(std::shared_ptr<std::unordered_map<std::string, std::string>> dictionary);
	void OutputProcessedText(std::shared_ptr<std::string> text);
	~CIOHandler();
private:
	void OpenFileForReading();
	void CreateMemoryMappingFile();
	void ClearFile(std::string const &file);
private:
	std::string m_inFileName;
	std::string m_outFileName;
	std::string m_dictionaryFileName;
	HANDLE m_handleMainFile;
	HANDLE m_mappingFileHandle;
	LONGLONG m_allRemainder;
	size_t m_remainderFragment;
	size_t m_viewLength;
	int m_innerCount;
	int m_innerCountForMMF; // MMF - memory mapping file
	bool m_isFileRead;
};