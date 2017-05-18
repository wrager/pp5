#include "Utils.h"
#include <fstream>
#include <string>

std::vector<int> CUtils::ReadDataFromFile(const std::string & fileName)
{
    std::ifstream inputFile(fileName);
    int val;

    std::vector<int> result;
    while(inputFile >> val)
    {
        result.push_back(val);
    }
    return result;
}