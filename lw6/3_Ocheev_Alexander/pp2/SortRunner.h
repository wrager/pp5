#pragma once
#include <fstream>
#include "AbstractSorter.h"
#include <string>
#include <vector>

template<class T>
class SortRunner
{
public:
    SortRunner(std::ifstream &input)
    {
        int number;
        while (input >> number)
        {
            vector.push_back(number);
        }
    }

    void Run(AbstractSorter<T> &sorter, const std::string &info, const std::string &outFileName)
    {
        sorter.SetVector(vector);

        auto startTime = std::clock();
        sorter.Sort();
        auto time = std::clock() - startTime;

        std::cout << info << time << std::endl;
        std::ofstream output(outFileName);
        PutVector(sorter.GetVector(), output);
    }

private:

    void PutVector(const std::vector<T> &vect, std::ostream &stream)
    {
        for (const auto &item : vect)
        {
            stream << item << " ";
        }
    }

    std::vector<T> vector;
};