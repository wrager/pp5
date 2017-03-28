// DictionaryComressor.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "IOManager.h"
#include "Compressor.h"
#include "Application.h"

using namespace std;

int main(int argc, char *argv[])
{
	CApplication app;
	CIOManager manager("ds.txt", "out.txt");
	CCompressor compressor;
	manager.SettingInputFile();
	while (true)
	{
		try
		{
			auto dataPtr = manager.GetViewMappingFile();
			compressor.SetTextFragment(dataPtr);
			compressor.SetLengthFragment(manager.GetSizeView());
			compressor.EditFragment();
			
		}
		catch (std::runtime_error)
		{
			break;
		}
	}
	manager.OutputDictionary(compressor.GetAllDictionary());
	manager.OutputProcessedText(compressor.GetAllProcessingText());

	
	
    return 0;
}

