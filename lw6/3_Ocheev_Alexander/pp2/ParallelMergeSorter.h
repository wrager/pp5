#pragma once
#include "AbstractMergeSorter.h"
#include <numeric>

template <class T>
class ParallelMergeSorter : public AbstractMergeSorter<T>
{
public:
    ParallelMergeSorter()
    {
        threadCount = std::thread::hardware_concurrency();
    }

    void Sort() override
    {
        Parallelize();
    }

private:
    void Parallelize()
    {
        std::vector<std::vector<T>> parts(threadCount);
        int interval = vector.size() / threadCount;

        for (int i = 0; i < parts.size(); i++)
        {
            int start = i * interval;
            int end = start + interval < vector.size() ? start + interval : vector.size();

            parts[i].resize(end - start);
            std::copy(vector.begin() + start, vector.begin() + end, parts[i].begin());
        }

        for (auto &part : parts)
        {
            part = SortParts(part);
        }

        vector = std::accumulate(parts.begin(), parts.end(), std::vector<T>(), [&](std::vector<T> &first, std::vector<T> &second) {
            std::vector<T> currentResult(first.size() + second.size());
            std::merge(first.begin(), first.end(), second.begin(), second.end(), currentResult.begin());
            return currentResult;
        });
    }

    int threadCount = 2;
};