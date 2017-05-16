#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <string>

#include "SortBatcher.h"

std::vector<unsigned> ReadFile(const std::string & nameFile)
{
	std::ifstream inpFile(nameFile);
	if (!inpFile.is_open())
	{
		std::cout << "File not found!";
		exit(1);
	}

	std::vector<unsigned> vecNum;
	while (!inpFile.eof())
	{
		std::string mainString;
		inpFile >> mainString;
		vecNum.push_back(atoi(mainString.c_str()));
	}
	
	return vecNum;
}

void WriteToFile(const std::string & nameFile, const std::vector<unsigned> & numArr)
{
	std::ofstream inpFile(nameFile);
	inpFile << "{ ";
	for (auto it : numArr)
	{
		inpFile << it << ", ";
	}
	inpFile << " }";
}

int main(int argc, char * argv[])
{
	if (argc == 3)
	{
		std::chrono::time_point<std::chrono::system_clock> startTime, endTime;

		startTime = std::chrono::system_clock::now();
		
		std::vector<unsigned> number = ReadFile(argv[1]);
		CSortBatcher sortBatch;
		std::vector<unsigned> res = sortBatch.sortBatcher(number);
		WriteToFile(argv[2], res);	 
			
		endTime = std::chrono::system_clock::now();
		std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << "ms" << std::endl;
	}
	return 0;
}