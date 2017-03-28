// DictionaryComressor.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using namespace std;
#define DIV 1024
#define WIDTH 7

#define BUF_SIZE 256
TCHAR szName[] = TEXT("ds.txt");



void ex(LPVOID *ret)
{
	setlocale(LC_ALL, "Rus");
	DWORD dwLength;
	__try
	{
		dwLength = *((LPDWORD)ret);
		std::cout << "dwLength = " << dwLength << std::endl;
	}
	__except (GetExceptionCode() == EXCEPTION_IN_PAGE_ERROR ?
		EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		std::cout << "Error! " << std::endl;
	}
}

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "Russian");
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	__int64 lpFreeBytesAvailable, lpTotalNumberOfBytes, lpTotalNumberOfFreeBytes;	
	auto count = GetDiskFreeSpaceEx(NULL,
		(PULARGE_INTEGER)&lpFreeBytesAvailable,
		(PULARGE_INTEGER)&lpTotalNumberOfBytes,
		(PULARGE_INTEGER)&lpTotalNumberOfFreeBytes
	);
	std::cout << "count = " << count << std::endl;
	std::cout << "GetLastError = " << GetLastError() << std::endl;
	std::cout << "lpFreeBytesAvailable = " << lpFreeBytesAvailable << std::endl;
	std::cout << "lpTotalNumberOfBytes = " << lpTotalNumberOfBytes << std::endl;
	std::cout << "lpTotalNumberOfFreeBytes = " << lpTotalNumberOfFreeBytes << std::endl;
	/*_tprintf(TEXT("%% используемой памяти используется . \ N"),
		WIDTH, statex.dwMemoryLoad);
	_tprintf(TEXT("%% I64d общий КБ физической памяти. \ N"),
		WIDTH, statex.ullTotalPhys / DIV);
	_tprintf(TEXT("Есть% * I64d свободного КБ физической памяти. \ N" ),
		WIDTH, statex.ullAvailPhys / DIV);
	_tprintf(TEXT("Общее количество килобайт файла подкачки% * I64d. \ N"),
		WIDTH, statex.ullTotalPageFile / DIV);
	_tprintf(TEXT("Есть% * I64d свободного КБ файла подкачки. \ N" ),
		WIDTH, statex.ullAvailPageFile / DIV);
	_tprintf(TEXT(" %% I64d общий объем виртуальной памяти. \ N"),
		WIDTH, statex.ullTotalVirtual / DIV);
	_tprintf(TEXT("Есть% * I64d свободного КБ виртуальной памяти. \ N" ),
	
	WIDTH, statex.ullAvailVirtual / DIV);*/
	
	std::cout << statex.dwMemoryLoad << string(" используемой памяти используется.") << std::endl;
	std::cout << statex.ullTotalPhys / DIV << string(" I64d общий КБ физической памяти..") << std::endl;
	std::cout << statex.ullAvailPhys / DIV << string(" свободного КБ физической памяти.") << std::endl;
	std::cout << statex.ullTotalPageFile / DIV << string("  Общее количество килобайт файла подкачки%.") << std::endl;
	std::cout << statex.ullAvailPageFile / DIV << string(" вободного КБ файла подкачки." )<< std::endl;
	std::cout << statex.ullTotalVirtual / DIV << string( " общий объем виртуальной памяти.") << std::endl;
	std::cout << statex.ullAvailVirtual / DIV << string(" свободного КБ виртуальной памяти.") << std::endl;
	
	// Показывать объем доступной расширенной памяти.
	//GlobalMemoryStatusEx();
	std::string file("ds.txt");
	std::cout << "(LPCWSTR)&file = " << (LPCWSTR)&file << std::endl;
	HANDLE handle = CreateFile(TEXT("ds.txt"),
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (handle == INVALID_HANDLE_VALUE)
	{
		printf("File Not Opened!\n");
		fflush(stdout);
		return 0;
	}
	else
		printf("File Opened!\n");

	std::cout << "GetLastError = " << GetLastError() << std::endl;
	//auto fileMapping = CreateFileMapping(handle, NULL, PAGE_EXECUTE_READ, 0, DWORD(lpFreeBytesAvailable / 5), LPCWSTR("inputFile"));
	auto fileMapping = CreateFileMapping(handle,
		NULL,
		PAGE_READWRITE,
		0, 
		0,//DWORD(lpFreeBytesAvailable / 5),
		TEXT("MyFileMappingObject"));
	if (fileMapping == NULL)
	{
		printf("%u - Error: CreateFileMapping()\n", GetLastError());
	}
	std::cout << "GetLastError = " << GetLastError() << std::endl;
	SYSTEM_INFO info;
	GetSystemInfo((LPSYSTEM_INFO)&info);
	std::cout << "info.dwAllocationGranularity = " << info.wProcessorLevel<< std::endl;


	auto dataPtr = (char*)MapViewOfFile(fileMapping, FILE_MAP_READ, 0, 0, CSingletonSystemInfo::GetInstance()->GetAllocationGranularity());
	std::cout << "GetLastError = " << GetLastError() << std::endl;
	std::string sName;
	for (size_t i = 0; i != CSingletonSystemInfo::GetInstance()->GetAllocationGranularity(); ++i)
	{
		sName = sName + dataPtr[i];
	}


	//CopyMemory((PVOID)returnMap, szMsg, (_tcslen(szMsg) * sizeof(TCHAR)));
	
	//char * buf = new char[info.dwAllocationGranularity];
	//CharToOemA(dataPtr, buf); 
	std::cout << "sName = " << sName.data() << std::endl;
	/*for (size_t i = 0; i != info.dwAllocationGranularity; ++i)
	{
		std::cout << dataPtr[i] << std::endl;
	}
	std::cout << dataPtr;*/
	//CSingletonSystemInfo::GetInstance()->GetAllocationGranularity();
	/*HANDLE hMapFile;
	LPCTSTR pBuf;
	auto name = (LPCWSTR)&string("/ds.txt");
	std::cout << name << std::endl;
	HANDLE handle2 = CreateFile(name , GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_READONLY, NULL);

	hMapFile = CreateFileMapping(
		handle2,    // use paging file
		NULL,                    // default security
		PAGE_READWRITE,          // read/write access
		0,                       // maximum object size (high-order DWORD)
		BUF_SIZE,                // maximum object size (low-order DWORD)
		szName);                 // name of mapping object

	if (hMapFile == NULL)
	{
		_tprintf(TEXT("Could not create file mapping object (%d).\n"),
			GetLastError());
		return 1;
	}
	pBuf = (LPTSTR)MapViewOfFile(hMapFile,   // handle to map object
		FILE_MAP_ALL_ACCESS, // read/write permission
		0,
		0,
		BUF_SIZE);
	*/
	/*if (returnMap == NULL)
	{
		_tprintf(TEXT("Could not map view of file (%d).\n"),
			GetLastError());

		CloseHandle(fileMapping);

		return 1;
	}*/

	/*std::cout << "szMsg = ";
	for (size_t i = 0; i != 65536; ++i)
	{
		std::cout << returnMap;
	}
	std::cout << std::endl;
	*/
	//_getch();

	//UnmapViewOfFile(returnMap);

	CloseHandle(fileMapping);
	
	
    return 0;
}

