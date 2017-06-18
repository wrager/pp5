#pragma once
#include <vector>
#include <algorithm>

template <class T>
class AbstractBatchersSorter
{
public:
    std::vector<T> Sort(const std::vector<T> &sourceVector)
    {
        vector = sourceVector;
        OddEvenMergeSort(0, vector.size());

        return vector;
    }

    virtual ~AbstractBatchersSorter() = default;

protected:
    /** sorts a piece of length n of the array
    *  starting at position lo */
    virtual void OddEvenMergeSort(size_t lo, size_t n) = 0;

    /** lo is the starting position and
    *  n is the length of the piece to be merged,
    *  r is the distance of the elements to be compared */
    virtual void OddEvenMerge(size_t lo, size_t n, size_t r) = 0;

    void Compare(size_t i, size_t j)
    {
        if (i >= vector.size() || j >= vector.size())
        {
            return;
        }

        if (vector[i] > vector[j])
        {
            std::swap(vector[i], vector[j]);
        }
    }

private:
    std::vector<T> vector;
};