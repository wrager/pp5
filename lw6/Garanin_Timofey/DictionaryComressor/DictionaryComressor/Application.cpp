#include "stdafx.h"
#include "Repository.h"
#include "IOManager.h"
#include "Compressor.h"
#include "Application.h"

CApplication::CApplication(CIOManager *manager)
	: m_iomanager(manager)
	, m_nextThreadOrderForWrite(0)
{
	m_myRepository = CMyRepository();
}

void CApplication::SetInputFileName(std::string const &name)
{
	m_iomanager->SetInputFileName(name);
}

void CApplication::SetOutputFileName(std::string const &name)
{
	m_iomanager->SetOutputFileName(name);
}


//TODO: переделать логику с потоками
//TODO: переделать , сделать общий репозиторий
//TODO: переделать на оперативную память
void CApplication::ProcessFile()
{
	try
	{
		m_iomanager->SettingInputFile();

		for (size_t i = 0; i != CSingletonSystemInfo::GetInstance()->GetNumberOfProcessors(); ++i)
		{
			m_threads.push_back(new CThreadWrapper(this));
			m_threads.back()->Run();
		}
		m_threads.clear();

		std::cout << "File processed" << std::endl;
		OutputResultsInFile();
		std::cout << "Results output in files" << std::endl;
		return;
	}
	catch (std::runtime_error const &ex)
	{
		std::cerr << "Error! " << ex.what() << std::endl;
		return;
	}
}

void CApplication::SaveNewInformation(CCompressor &compressor)
{
	m_myRepository.SetNewDictionaryFragment(compressor.GetAllDictionary());
	m_myRepository.SetNewTextFragment(compressor.GetAllProcessingText());
}

void CApplication::OutputResultsInFile()
{
	m_iomanager->OutputDictionary(m_myRepository.GetDictionary());
	m_iomanager->OutputProcessedText(m_myRepository.GetText());
}

void CApplication::Wait() const
{
	for (auto &thread : m_threads)
	{
		thread->Join();
	}
}

bool CApplication::EditNextFragment()
{
	try
	{
		m_mutex.lock();
		CCompressor compressor(m_iomanager->GetOrder());
		auto dataPtr = m_iomanager->GetViewMappingFile();
		m_mutex.unlock();
		compressor.SetTextFragment(dataPtr);
		compressor.SetLengthFragment(m_iomanager->GetSizeView());
		compressor.EditFragment();

		while (true)
		{
			if (compressor.GetOrder() == m_nextThreadOrderForWrite)
			{
				m_mutex.lock();
				SaveNewInformation(compressor);
				m_mutex.unlock();
				++m_nextThreadOrderForWrite;
				break;
			}
			else
			{
				std::this_thread::sleep_for(std::chrono::seconds(2));
			}
		}
		return true;
	}
	catch (std::runtime_error)
	{
		m_mutex.unlock();
		return false;
	}
}

CApplication::~CApplication()
{
	delete m_iomanager;
}
