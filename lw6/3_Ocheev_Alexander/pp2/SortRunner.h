#pragma once
#include <fstream>
#include "AbstractSortWriter.h"

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

    void Run()
    {
        sortWriter->Write(vector);
    }

    void SetWriter(AbstractSortWriter<T> *writer)
    {
        sortWriter = writer;
    }

private:

    std::vector<T> vector;

    AbstractSortWriter<T> *sortWriter;
};