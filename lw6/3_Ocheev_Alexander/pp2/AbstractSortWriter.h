#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <ctime>

template<class T>
class AbstractSortWriter
{
public:
    virtual void Write(const std::vector<T> &sourceVector) = 0;

protected:
    void PutVector(const std::vector<T> &vect, std::ostream &stream)
    {
        for (const auto &item : vect)
        {
            stream << item << " ";
        }
    }
};