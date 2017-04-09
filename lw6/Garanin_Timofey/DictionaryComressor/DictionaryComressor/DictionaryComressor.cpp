#include "stdafx.h"
#include "IOManager.h"
#include "Repository.h"
#include "Compressor.h"
#include "Application.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cerr << "Usage program.exe <input_file.txt> <output_file.txt>" << std::endl;
		return EXIT_FAILURE;
	}
	CSingletonSystemInfo::GetInstance()->Output();
	CApplication app(new CIOManager(argv[1], argv[2]));
	app.ProcessFile();
	app.OutputResultsInFile();
	std::cout << "Results output in files" << std::endl;
    return EXIT_SUCCESS;
}

