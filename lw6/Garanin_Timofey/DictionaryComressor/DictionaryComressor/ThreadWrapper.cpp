#include "stdafx.h"
#include <thread>
#include "IOManager.h"
#include "RepositoryProcessedData.h"
#include "Compressor.h"
#include "Application.h"
#include "ThreadWrapper.h"

CThreadWrapper::CThreadWrapper(CApplication *app)
{
	m_thread = std::thread(&CApplication::ThreadFunction, app);
}

void CThreadWrapper::Join()
{
	if (m_thread.joinable())
	{
		m_thread.join();
	}
}