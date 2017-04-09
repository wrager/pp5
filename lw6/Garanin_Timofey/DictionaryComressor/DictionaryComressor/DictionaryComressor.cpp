#include "stdafx.h"
#include "IOManager.h"
#include "Compressor.h"
#include "Repository.h"
#include "Application.h"

using namespace std;

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cerr << "Usage program.exe <input_file.txt> <output_file.txt>" << std::endl;
		return EXIT_FAILURE;
	}
	CApplication app(new CIOManager(argv[1], argv[2]));
	app.ProcessFile();
	app.OutputResultsInFile();
    return EXIT_SUCCESS;
}

