#pragma once



class CCustomThread
{
public:
	CCustomThread(CApplication *app);
	void Run();
	bool IsFinished();
	//~CCustomThread();
	void Checked();
	bool IsChecked();
private:
	std::thread m_thread;
	CApplication *m_app;
	bool m_isFinished;
	bool m_isChecked;
};