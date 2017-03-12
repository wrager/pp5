// lw5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdlib.h>
#include "Application.h"
#include <exception>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		return EXIT_FAILURE;
	}
	
	try {
		CApplication app(argv[1]);
		app.SortArray();
		app.OutputResults();
	}
	catch (const std::exception& err)
	{
		std::cout << err.what() << std::endl;
	}


    return EXIT_SUCCESS;
}

