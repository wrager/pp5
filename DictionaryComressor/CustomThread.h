#pragma once

typedef void (CAppManager::*ThreadFunction)() const;

class CCustomThread
{
public:
	CCustomThread(CAppManager *app);
	void Join();
private:
	std::thread m_thread;
	CAppManager *m_app;
};