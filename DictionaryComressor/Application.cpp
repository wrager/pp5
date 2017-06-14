#include "stdafx.h"
#include "IOHandler.h"
#include "Repository.h"
#include "Compressor.h"
#include "Application.h"
#include "CustomThread.h"

CAppManager::CAppManager(CIOHandler *manager)
	: m_iohandler(manager)
	, m_nextNumberThreadForWrite(0)
{
	m_repository = CRepository();
}

void CAppManager::SetInputFileName(std::string const &name)
{
	m_iohandler->SetInputFileName(name);
}

void CAppManager::SetOutputFileName(std::string const &name)
{
	m_iohandler->SetOutputFileName(name);
}

void CAppManager::ProcessFile()
{
	try
	{
		while (!m_iohandler->IsFileRead())
		{
			m_iohandler->PrepareEnvironment();

			for (size_t i = 0; i != CSingletonSystemInfo::GetInstance()->GetNumberOfProcessors(); ++i)
			{
				m_mthreads.push_back(new std::thread(&CAppManager::CompressFragment, this));
			}
			
			for (auto &thread : m_mthreads)
			{
				if ((*thread).joinable())
					thread->join();
			}

			m_mthreads.clear();
		}
		std::cout << "File processed" << std::endl;
		return;
	}
	catch (std::runtime_error const &ex)
	{
		std::cerr << "Error! " << ex.what() << std::endl;
		return;
	}
}

void CAppManager::SetNewTextFragment(CCompressor &compressor)
{
	m_repository.SetNewTextFragment(compressor.GetAllProcessingText());
}

void CAppManager::SaveResult()
{
	m_iohandler->OutputDictionary(m_repository.GetDictionary());
	m_iohandler->OutputProcessedText(m_repository.GetText());

	std::cout << "Results output in files" << std::endl;
}


void CAppManager::CompressFragment()
{
	bool success = true;

	while (success)
	{
		try
		{
			m_mutex.lock();
			CCompressor compressor(m_iohandler->GetOrder(), &m_repository, &m_compressorMutex);
			auto dataPtr = m_iohandler->GetViewMappingFile();
			m_mutex.unlock();

			compressor.SetTextFragment(dataPtr);
			compressor.SetLengthFragment(m_iohandler->GetSizeView());
			compressor.ProcessFragment();

			while (true)
			{
				if (compressor.GetOrder() == m_nextNumberThreadForWrite)
				{
					m_mutex.lock();
					SetNewTextFragment(compressor);
					m_mutex.unlock();
					++m_nextNumberThreadForWrite;
					break;
				}
				else
				{
					std::this_thread::sleep_for(std::chrono::seconds(1));
				}
			}
		}
		catch (std::runtime_error)
		{
			m_mutex.unlock();
			success = false;
		}
	}
}

CAppManager::~CAppManager()
{
	delete m_iohandler;
}
