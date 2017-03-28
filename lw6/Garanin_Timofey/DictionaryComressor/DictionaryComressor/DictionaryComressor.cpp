// DictionaryComressor.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "IOManager.h"

using namespace std;

int main(int argc, char *argv[])
{
	CIOManager manager("ds.txt", "out.txt");
	manager.SettingInputFile();
	auto dataPtr = manager.GetViewMappingFile();
	std::string sName;
	for (size_t i = 0; i != manager.GetSizeView(); ++i)
	{
		sName = sName + dataPtr[i];
	}
	std::cout << "sName = " << sName.data() << std::endl;
	while (true)
	{
		try
		{
			dataPtr = manager.GetViewMappingFile();
		}
		catch (std::runtime_error)
		{
			break;
		}
	}
	

	
	
    return 0;
}

