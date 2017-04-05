#include "stdafx.h"
#include <thread>
#include "IOManager.h"
#include "Compressor.h"
#include "Repository.h"
#include "Application.h"
#include "CustomThread.h"


namespace
{
	void ThreadFunction(CApplication *app, bool &isFinished)
	{
		while (app->EditNextFragment()) {}
		isFinished = true;
	}
}

CCustomThread::CCustomThread(CApplication *app)
	: m_app(app)
	, m_isFinished(false)
	, m_isChecked(false)
{}

void CCustomThread::Run()
{
	m_thread = std::thread(ThreadFunction, m_app, std::ref(m_isFinished));
	return;
}

bool CCustomThread::IsFinished()
{
	return m_isFinished;
}

void CCustomThread::Checked()
{
	m_isChecked = true;
}

bool CCustomThread::IsChecked()
{
	return m_isChecked;
}
