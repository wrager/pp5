#pragma once
#include "AbstractSorter.h"
#include <thread>

template <class T>
class ParallelShellSorter : public AbstractSorter<T>
{
public:
    void Sort()
    {
        throw std::exception("no impl");
    }
};