// lab5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "BatchersAlgorithm.h"
typedef std::vector<std::vector<int>> Vector;


Vector GetDataFromFile(std::string fileName)
{
	std::ifstream file(fileName);
	std::string inputStr;
	std::vector<int> data;
	while (std::getline(file, inputStr))
	{
		std::stringstream str(inputStr);
		while (!str.eof())
		{
			std::string character;
			str >> character;
			data.push_back(atoi(character.c_str()));
		}
	}

	Vector result;
	result.push_back(data);
	return result;
}




void PrintData(Vector data)
{
	int resutlIndex = 0;
	for (auto el : data.at(resutlIndex))
	{
		std::cout << el << " ";
	}
}

int main()
{
	CBatchersAlgorithm batchersAlgorithm;
	Vector result = batchersAlgorithm.BatchersMergeSort(GetDataFromFile("input.txt"));
	PrintData(result);
    return EXIT_SUCCESS;
}

