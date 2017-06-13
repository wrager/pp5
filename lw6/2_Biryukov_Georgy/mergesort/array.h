#pragma once

class ArrayManager
{
private:
	std::vector <int> ReadFromFile(std::string fileName);
	std::vector<int> filledArray;
};