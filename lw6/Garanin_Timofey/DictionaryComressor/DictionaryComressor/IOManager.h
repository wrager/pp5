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
	~CIOManager();
private:
	void OpenFileForReading();
	void CreateMemoryMappingFile();



private:
	std::string m_inputFileName;
	std::string m_outputFileName;
	HANDLE m_fileHandle;
	HANDLE m_mappingFileHandle;
	int m_innerCount;
	LONGLONG m_fileLenght;
	size_t m_remainderLength;
};