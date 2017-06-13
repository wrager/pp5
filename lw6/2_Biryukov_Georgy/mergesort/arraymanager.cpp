#include "stdafx.h"
#include "arraymanager.h"

std::vector<int> ArrayManager::ReadFromFile(std::string fileName)
{
	std::vector <int> filledArray;
	ifstream file(fileName);
	int i;

	while (!file.eof())
	{
		file >> i;
		filledArray.push_back(i);
	}
	return filledArray;
}