#pragma once






class CIOManager
{
public:
	CIOManager(std::string const &inFile, std::string const &outFile);
	CIOManager();
	void SettingInputFile();
	char* GetViewMappingFile();
	size_t GetSizeView() const;
	void SetInputFileName(std::string const &name);
	void SetOutputFileName(std::string const &name);
	void OutputDictionary(std::shared_ptr<std::unordered_map<std::string, size_t>> dictionary);
	void OutputProcessedText(std::shared_ptr<std::string> text);
	~CIOManager();
	
private:
	void OpenFileForReading();
	void CreateMemoryMappingFile();
	void ClearFile(std::string const &file);
private:
	std::string m_inputFileName;
	std::string m_outputFileName;
	std::string m_dictionaryFileName;
	HANDLE m_fileHandle;
	HANDLE m_mappingFileHandle;
	int m_innerCount;
	LONGLONG m_fileLenght;
	size_t m_remainderLength;
	size_t m_viewLength;
};