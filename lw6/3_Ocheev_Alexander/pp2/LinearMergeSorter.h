#pragma once
#include "AbstractMergeSorter.h"

template <class T>
class LinearMergeSorter : public AbstractMergeSorter<T>
{
public:
    LinearMergeSorter() = default;

    void Sort() override
    {
        SortParts(vector);
    }
};