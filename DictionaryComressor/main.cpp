#include "stdafx.h"
#include "IOHandler.h"
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

	CAppManager app(new CIOHandler(argv[1], argv[2]));
	app.ProcessFile();
	app.SaveResult();
	return EXIT_SUCCESS;
}

