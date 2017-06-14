#include "stdafx.h"
#include <thread>
#include "IOHandler.h"
#include "Repository.h"
#include "Compressor.h"
#include "Application.h"
#include "CustomThread.h"

CCustomThread::CCustomThread(CAppManager *app)
{
	m_thread = std::thread(&CAppManager::ThreadFunction, app);
}

void CCustomThread::Join()
{
	if (m_thread.joinable())
	{
		m_thread.join();
	}
}