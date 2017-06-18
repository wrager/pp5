#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "AbstractBatchersMerge.h"
#include "LinearBatchersSorter.h"
#include "ParallelBatchersSort.h"

template<class T>
struct FileHandlerUtil
{
    clock_t time;
    std::vector<T> vector;
};

template<class T>
class FileHandler
{
public:
    static void Sort(std::istream &input)
    {
        auto source = GetVector(input);
        FileHandlerUtil<T> util;

        std::ofstream linearOut("linear.txt");
        LinearBatchersSorter<T> linear;
        auto result = Sort(linear, source);
        PutVector(result.vector, linearOut);
        std::cout << "linear time: " << result.time << std::endl;

        std::ofstream parallelOut("parallel.txt");
        ParallelBatchersSorter<T> parallel;
        result = Sort(parallel, source);
        PutVector(result.vector, parallelOut);
        std::cout << "parallel time: " << result.time << std::endl;
    }

private:
    static FileHandlerUtil<T> Sort(AbstractBatchersSorter<T> &sorter, const std::vector<T> &source)
    {
        FileHandlerUtil<T> result;

        result.time = clock();
        result.vector = sorter.Sort(source);
        result.time = clock() - result.time;

        return result;
    }

    static std::vector<T> GetVector(std::istream &stream)
    {
        std::vector<T> result;
        int number;
        while (stream >> number)
        {
            result.push_back(number);
        }

        return result;
    }

    static void PutVector(const std::vector<T> &vect, std::ostream &stream)
    {
        for (const auto &item : vect)
        {
            stream << item << " ";
        }
    }
};