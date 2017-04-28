#include "stdafx.h" 
#include "GammaCoding.h"

int main(int argc, char *argv[])
{
	srand(unsigned int (time(0)));
	if (argc == 3)
	{
		CGammaCoding code;
		code.StartProgram(argv[1], argv[2]);
	}
	else
	{
		std::cout << "error argv, input coding.exe filename.txt thread_num";
	}
	return 0;
}
