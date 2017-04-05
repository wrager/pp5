#include "stdafx.h"
#include "IOManager.h"
#include <fstream>
#include <iterator>
#include <sstream>
#include <algorithm>

namespace
{
	std::string toString(std::pair<std::string, size_t> const &data)
	{
		std::ostringstream str;
		str << data.first << ":" << data.second;
		return str.str();
	}
}

CIOManager::CIOManager(std::string const & inFile, std::string const & outFile)
	: m_inputFileName(inFile)
	, m_outputFileName(outFile)
	, m_dictionaryFileName("dictionary.txt")
	, m_innerCount(0)
{
	ClearFile(m_outputFileName);
	ClearFile(m_dictionaryFileName);
	setlocale(LC_ALL, "Russian");
}

CIOManager::CIOManager()
	: m_innerCount(0)
{
	setlocale(LC_ALL, "Russian");
}

void CIOManager::SettingInputFile()
{
	try
	{
		OpenFileForReading();
		CreateMemoryMappingFile();
	}
	catch (std::runtime_error)
	{
		return;
	}
}

char* CIOManager::GetViewMappingFile()
{
	try
	{
		if (m_remainderLength < 0)
		{
			throw std::runtime_error("File ended");
		}
		DWORD lastError1 = GetLastError();
		auto allocationGranularity = CSingletonSystemInfo::GetInstance()->GetAllocationGranularity();
		char* data = nullptr;
		if (m_remainderLength < allocationGranularity)
		{
			data = (char*)MapViewOfFile(m_mappingFileHandle, FILE_MAP_READ, 0, allocationGranularity * m_innerCount++, m_remainderLength);
			m_viewLength = m_remainderLength;
		}
		else
		{
			data = (char*)MapViewOfFile(m_mappingFileHandle, FILE_MAP_READ, 0, allocationGranularity * m_innerCount++, allocationGranularity);
			m_viewLength = allocationGranularity;
		}
		m_remainderLength -= allocationGranularity;
		DWORD lastError = GetLastError();
		if (lastError != 0 && lastError1 != lastError)
		{
			std::cout << "Failed to come at view mapping file. Error: " << lastError << std::endl;
			throw std::runtime_error("Failed to come at view mapping file");
		}
		else
		{
			std::cout << "Accessed" << std::endl;
			return data;
		}
	}
	catch (std::runtime_error const &ex)
	{
		throw ex;
	}
}

size_t CIOManager::GetSizeView() const
{
	return m_viewLength;
}

void CIOManager::SetInputFileName(std::string const & name)
{
	m_inputFileName = name;
}

void CIOManager::SetOutputFileName(std::string const & name)
{
	m_outputFileName = name;
}

void CIOManager::OutputDictionary(std::shared_ptr<std::unordered_map<std::string, size_t>> dictionary)
{
	std::ofstream file(m_dictionaryFileName, std::ios::app);
	std::transform(dictionary->begin(), dictionary->end(), std::ostream_iterator<std::string>(file, ";"), toString);
}

void CIOManager::OutputProcessedText(std::shared_ptr<std::string> text)
{
	std::ofstream file(m_outputFileName, std::ios::app);
	file << text->data();
}

CIOManager::~CIOManager()
{
	CloseHandle(m_fileHandle);
	CloseHandle(m_mappingFileHandle);
}

void CIOManager::OpenFileForReading()
{
	try
	{
		m_fileHandle = CreateFileA((LPCSTR)m_inputFileName.data(),
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (m_fileHandle == INVALID_HANDLE_VALUE)
		{
			throw std::runtime_error("File Not Opened! " + GetLastError());
		}
		else
			std::cout << "File Opened!\n";

		DWORD dwSizeHigh = 0, dwSizeLow = 0;
		dwSizeLow = GetFileSize(m_fileHandle, &dwSizeHigh);
		m_fileLenght = (dwSizeHigh * (MAXDWORD + 1)) + dwSizeLow;
		m_remainderLength = m_fileLenght;
		if (m_fileLenght > CSingletonSystemInfo::GetInstance()->GetAllocationGranularity())
		{
			m_fileLenght = CSingletonSystemInfo::GetInstance()->GetAllocationGranularity();
		}
	}
	catch (std::runtime_error const &ex)
	{
		throw ex;
	}
}

void CIOManager::CreateMemoryMappingFile()
{
	try
	{
		m_mappingFileHandle = CreateFileMapping(m_fileHandle,
			NULL,
			PAGE_READWRITE,
			0,
			0,//DWORD(lpFreeBytesAvailable / 5),
			TEXT("MyFileMappingObject"));
		if (m_mappingFileHandle == NULL)
		{
			std::cout << "Failed to create file mapping. Error: " << GetLastError() << std::endl;
			throw std::runtime_error("Failed to create file mapping");
		}
	}
	catch (std::runtime_error const &ex)
	{
		throw ex;
	}
}

void CIOManager::ClearFile(std::string const & file)
{
	std::ofstream f(file);
	f.clear();
}
