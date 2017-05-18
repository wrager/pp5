#pragma once
#include <vector>

class CUtils
{
public:
    static std::vector<int> ReadDataFromFile(const std::string & fileName = "input.txt");
};