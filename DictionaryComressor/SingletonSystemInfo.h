#pragma once

class CSingletonSystemInfo
{
public:
	static CSingletonSystemInfo * GetInstance();
	~CSingletonSystemInfo();
	DWORD GetAllocationGranularity() const; // Гранулярность распределения, нужно для получение отражения на память где храниться файл в куче.  65536 - 2^16
	DWORD_PTR GetActiveProcessorMask() const;
	DWORD GetNumberOfProcessors() const; // Количество процессоров компьютера
	DWORDLONG GetUllAvailPhys() const; // Количество свободной оперативной памяти компьютера, которую можно использовать
private:
	CSingletonSystemInfo();
	CSingletonSystemInfo(const CSingletonSystemInfo&);
	CSingletonSystemInfo& operator=(CSingletonSystemInfo&) {};
private:
	static CSingletonSystemInfo * m_pInstance;
	SYSTEM_INFO m_systemInfo;
	MEMORYSTATUSEX m_statex;
};