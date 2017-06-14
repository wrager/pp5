#include "stdafx.h"
#include "SingletonSystemInfo.h"

CSingletonSystemInfo * CSingletonSystemInfo::m_pInstance = 0;

CSingletonSystemInfo::CSingletonSystemInfo()
{
	GetSystemInfo((LPSYSTEM_INFO)&m_systemInfo);
	m_statex.dwLength = sizeof(m_statex);
	GlobalMemoryStatusEx(&m_statex);
}

CSingletonSystemInfo * CSingletonSystemInfo::GetInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new CSingletonSystemInfo();
	}
	return m_pInstance;
}

CSingletonSystemInfo::~CSingletonSystemInfo()
{
	delete m_pInstance;
}

DWORD CSingletonSystemInfo::GetAllocationGranularity() const
{
	return m_systemInfo.dwAllocationGranularity;
}

DWORD_PTR CSingletonSystemInfo::GetActiveProcessorMask() const
{
	return m_systemInfo.dwActiveProcessorMask;
}

DWORD CSingletonSystemInfo::GetNumberOfProcessors() const
{
	return m_systemInfo.dwNumberOfProcessors;
}

DWORDLONG CSingletonSystemInfo::GetUllAvailPhys() const
{
	return m_statex.ullAvailPhys;
}
