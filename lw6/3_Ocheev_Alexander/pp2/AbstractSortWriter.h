#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <ctime>
#include "AbstractSorter.h"

template<class T>
class AbstractSortWriter
{
public:
    virtual void Write(const std::vector<T> &sourceVector) = 0;

    virtual ~AbstractSortWriter() = default;

protected:
    void PutVector(const std::vector<T> &vect, std::ostream &stream)
    {
        for (const auto &item : vect)
        {
            stream << item << " ";
        }
    }

    AbstractSorter<T> *sorter;
};