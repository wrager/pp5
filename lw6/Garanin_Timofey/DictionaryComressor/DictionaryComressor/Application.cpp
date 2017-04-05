#include "stdafx.h"
#include "IOManager.h"
#include "Compressor.h"
#include "Application.h"
#include "CustomThread.h"

bool ThreadFunction(CApplication *app)
{
	return app->EditNextFragment();
}


CApplication::CApplication(CIOManager *manager)
	: m_iomanager(manager)
{
}

void CApplication::SetInputFileName(std::string const &name)
{
	m_iomanager->SetInputFileName(name);
}

void CApplication::SetOutputFileName(std::string const &name)
{
	m_iomanager->SetOutputFileName(name);
}

void CApplication::ProcessFile()
{
	try
	{
		m_iomanager->SettingInputFile();
		int innerCount = 0;
		std::vector<CCustomThread*> threads;

		for (size_t i = 0; i != CSingletonSystemInfo::GetInstance()->GetNumberOfProcessors() - 1; ++i)
		{
			threads.push_back(new CCustomThread(this));
			threads.back()->Run();
		}
		while (ThreadFunction(this)) {}
		int i = threads.size() - 1;
		int numberThreadsFinishedWorking = 0;
		while (numberThreadsFinishedWorking < threads.size())
		{
			if (threads.at(i)->IsFinished() && !threads.at(i)->IsChecked())
			{
				threads.at(i)->Checked();
				++numberThreadsFinishedWorking;
			}
			--i;
			if (i == -1)
			{
				i = threads.size() - 1;
				std::this_thread::sleep_for(std::chrono::seconds(2));
			}

		}
		threads.clear();
		std::cout << "File processed" << std::endl;
		return;
	}
	catch (std::runtime_error const &ex)
	{
		std::cerr << "Error! " << ex.what() << std::endl;
		return;
	}
}

void CApplication::OutputResultsInFiles(CCompressor &compressor)
{
	m_iomanager->OutputDictionary(compressor.GetAllDictionary());
	m_iomanager->OutputProcessedText(compressor.GetAllProcessingText());
}

bool CApplication::EditNextFragment()
{
	std::mutex mutex;
	try
	{
		
		mutex.lock();
		auto dataPtr = m_iomanager->GetViewMappingFile();
		mutex.unlock();
		CCompressor compressor;
		compressor.SetTextFragment(dataPtr);
		compressor.SetLengthFragment(m_iomanager->GetSizeView());
		
		compressor.EditFragment();
		this->OutputResultsInFiles(compressor);
		return true;
	}
	catch (std::runtime_error const &ex)
	{
		mutex.unlock();
		return false;
	}
}

CApplication::~CApplication()
{
	delete m_iomanager;
}
