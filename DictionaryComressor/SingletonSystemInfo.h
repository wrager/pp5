#pragma once

class CSingletonSystemInfo
{
public:
	static CSingletonSystemInfo * GetInstance();
	~CSingletonSystemInfo();
	DWORD GetAllocationGranularity() const; // ������������� �������������, ����� ��� ��������� ��������� �� ������ ��� ��������� ���� � ����.  65536 - 2^16
	DWORD_PTR GetActiveProcessorMask() const;
	DWORD GetNumberOfProcessors() const; // ���������� ����������� ����������
	DWORDLONG GetUllAvailPhys() const; // ���������� ��������� ����������� ������ ����������, ������� ����� ������������
private:
	CSingletonSystemInfo();
	CSingletonSystemInfo(const CSingletonSystemInfo&);
	CSingletonSystemInfo& operator=(CSingletonSystemInfo&) {};
private:
	static CSingletonSystemInfo * m_pInstance;
	SYSTEM_INFO m_systemInfo;
	MEMORYSTATUSEX m_statex;
};