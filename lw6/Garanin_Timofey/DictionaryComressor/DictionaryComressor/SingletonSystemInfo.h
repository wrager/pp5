#pragma once


class CSingletonSystemInfo
{
public:
	static CSingletonSystemInfo * GetInstance();
	~CSingletonSystemInfo();
	DWORD GetAllocationGranularity() const;
	DWORD_PTR GetActiveProcessorMask() const;
	DWORD GetNumberOfProcessors() const;
private:
	CSingletonSystemInfo();
	CSingletonSystemInfo(const CSingletonSystemInfo&);
	CSingletonSystemInfo& operator=(CSingletonSystemInfo&) {};
private:
	static CSingletonSystemInfo * m_pInstance;
	SYSTEM_INFO m_systemInfo;
};