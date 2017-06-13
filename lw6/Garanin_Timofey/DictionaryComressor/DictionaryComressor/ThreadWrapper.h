#pragma once

typedef void (CApplication::*ThreadFunction)() const;

class CThreadWrapper
{
public:
	CThreadWrapper(CApplication *app);
	void Join();
private:
	std::thread m_thread;
	CApplication *m_app;
};