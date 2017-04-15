#pragma once
#include "AbstractSorter.h"

template <class T>
class ParallelMergeSorter : public AbstractSorter<T>
{
public:
    void Sort()
    {
        throw std::exception("no impl");
    }
};