// GetPi.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "main.h"
#include <omp.h>

using namespace std;

void CheckParametrs(int argc)
{
	if (argc != AMOUNT_ARGUMENTS)
	{
		throw invalid_argument(MESSAGE_INCORRECT_AMOUNT_ARGUMENTS
			+ to_string(AMOUNT_ARGUMENTS));
	}
}


int main(int argc, char *argv[])
{
	try
	{
		setlocale(LC_ALL, "RUS");

		CheckParametrs(argc);

		boost::timer::cpu_timer timer;

		size_t amountIteration = atoi(argv[1]);
		size_t processsNumber = atoi(argv[2]);

		CTaskSolver taskExecutor;

		timer.start();
		cout << taskExecutor.GetPi(amountIteration, processsNumber) << std::endl;
		timer.stop();

		// TODO : see need comment low
		double time = timer.elapsed().wall * pow(10.f, -9.f);// / amountThread;
		std::cout << "time = " << time << std::endl;
		
		omp_set_dynamic(0);
		omp_set_num_threads(10);
		#pragma omp parallel
		{
			printf("Hello World\n");
		}

		system("pause");
		//taskExecutor.m_outputChannel.Close();
	}
	catch (const std::exception & exception)
	{
		std::cout << exception.what() << std::endl;
		system("pause");
		return 1;
	}

	return 0;
}

