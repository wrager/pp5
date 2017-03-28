#pragma once






class CIOManager
{
public:
	CIOManager(std::string const &inFile, std::string const &outFile);
	void SettingInputFile();
	char* GetViewMappingFile();
	size_t GetSizeView() const;
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