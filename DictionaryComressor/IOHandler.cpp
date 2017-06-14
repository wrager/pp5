#include "stdafx.h"
#include "IOHandler.h"
#include <fstream>
#include <iterator>
#include <sstream>
#include <algorithm>

namespace
{
	std::string toString(std::pair<std::string, std::string> const &data)
	{
		std::ostringstream str;
		str << data.first << ":" << data.second;
		return str.str();
	}
}

CIOHandler::CIOHandler(std::string const & inFile, std::string const & outFile)
	: m_inFileName(inFile)
	, m_outFileName(outFile)
	, m_dictionaryFileName("newDictionary.txt")
	, m_innerCount(0)
	, m_innerCountForMMF(0)
	, m_isFileRead(false)
{
	ClearFile(m_outFileName);
	ClearFile(m_dictionaryFileName);
	setlocale(LC_ALL, "Russian");
}

CIOHandler::CIOHandler()
	: m_innerCount(0)
{
	setlocale(LC_ALL, "Russian");
}

int CIOHandler::GetOrder() const
{
	return m_innerCount;
}

bool CIOHandler::IsFileRead() const
{
	return m_isFileRead;
}

void CIOHandler::PrepareEnvironment()
{
	try
	{
		if (!m_handleMainFile)
		{
			OpenFileForReading();
		}
		CreateMemoryMappingFile();
	}
	catch (std::runtime_error const &ex)
	{
		throw ex;
	}
}

char* CIOHandler::GetViewMappingFile()
{
	try
	{
		if (m_remainderFragment < 0)
		{
			throw std::runtime_error("File ended");
		}
		DWORD lastError1 = GetLastError();
		auto allocationGranularity = CSingletonSystemInfo::GetInstance()->GetAllocationGranularity();
		char* data = nullptr;

		if (m_remainderFragment < allocationGranularity)
		{
			data = (char*)MapViewOfFile(m_mappingFileHandle, FILE_MAP_READ, 0, allocationGranularity * m_innerCount++, m_remainderFragment);
			m_viewLength = m_remainderFragment;
		}
		else
		{
			data = (char*)MapViewOfFile(m_mappingFileHandle, FILE_MAP_READ, 0, allocationGranularity * m_innerCount++, allocationGranularity);
			m_viewLength = allocationGranularity;
		}

		m_remainderFragment -= allocationGranularity;
		DWORD lastError = GetLastError();
		
		if (lastError != 0 && lastError1 != lastError)
		{
			throw std::runtime_error("Failed to come at view mapping file");
		}
		else
		{
			std::cout << "Received data fragment" << std::endl;
			return data;
		}
	}
	catch (std::runtime_error const &ex)
	{
		throw ex;
	}
}

size_t CIOHandler::GetSizeView() const
{
	return m_viewLength;
}

void CIOHandler::SetInputFileName(std::string const & name)
{
	m_inFileName = name;
}

void CIOHandler::SetOutputFileName(std::string const & name)
{
	m_outFileName = name;
}

void CIOHandler::OutputDictionary(std::shared_ptr<std::unordered_map<std::string, std::string>> dictionary)
{
	std::ofstream file(m_dictionaryFileName, std::ios::app);
	std::transform(dictionary->begin(), dictionary->end(), std::ostream_iterator<std::string>(file, "\n"), toString);
}

void CIOHandler::OutputProcessedText(std::shared_ptr<std::string> text)
{
	std::ofstream file(m_outFileName, std::ios::app);
	file << text->data();
}

CIOHandler::~CIOHandler()
{
	CloseHandle(m_handleMainFile);
	CloseHandle(m_mappingFileHandle);
}

void CIOHandler::OpenFileForReading()
{
	try
	{
		m_handleMainFile = CreateFileA((LPCSTR)m_inFileName.data(),
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (m_handleMainFile == INVALID_HANDLE_VALUE)
		{
			throw std::runtime_error("File Not Opened! " + GetLastError());
		}
		else
		{
			std::cout << "File Opened!\n";
		}

		DWORD dwSizeHigh = 0, dwSizeLow = 0;
		dwSizeLow = GetFileSize(m_handleMainFile, &dwSizeHigh);
		m_allRemainder = (dwSizeHigh * (MAXDWORD + 1)) + dwSizeLow;
	}
	catch (std::runtime_error const &ex)
	{
		throw ex;
	}
}

void CIOHandler::CreateMemoryMappingFile()
{
	try
	{
		m_remainderFragment = m_allRemainder;
		DWORDLONG availPhys = CSingletonSystemInfo::GetInstance()->GetUllAvailPhys();
		DWORDLONG twentyPercentOfAvailPhys = availPhys / 5;
		DWORD size;
		if (DWORDLONG(m_remainderFragment) < twentyPercentOfAvailPhys)
		{
			size = DWORD(m_remainderFragment);
			m_allRemainder = 0;
			m_isFileRead = true;
		}
		else
		{
			size = DWORD(twentyPercentOfAvailPhys);
			m_allRemainder -= twentyPercentOfAvailPhys;
		}
		m_mappingFileHandle = CreateFileMapping(m_handleMainFile,
			NULL,
			PAGE_READWRITE,
			m_innerCountForMMF * size,
			size,
			TEXT("MyFileMappingObject"));
		if (m_mappingFileHandle == NULL)
		{
			throw std::runtime_error("Failed to create file mapping");
		}
	}
	catch (std::runtime_error const &ex)
	{
		throw ex;
	}
}

void CIOHandler::ClearFile(std::string const & file)
{
	std::ofstream f(file);
	f.clear();
}
