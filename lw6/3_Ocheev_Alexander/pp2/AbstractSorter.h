#pragma once
#include <vector>

template <class T>
class AbstractSorter
{
public:
    void SetVector(const std::vector<T>& sourceVector)
    {
        vector = sourceVector;
    }

    virtual void Sort() = 0;

    std::vector<T> GetVector()
    {
        return vector;
    }

    virtual ~AbstractSorter() = default;

protected:
    std::vector<T> vector;
};