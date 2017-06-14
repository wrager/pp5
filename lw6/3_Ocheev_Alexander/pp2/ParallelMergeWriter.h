#pragma once
#include "AbstractSortWriter.h"
#include "ParallelMergeSorter.h"

template <class T>
class ParallelMergeWriter : public AbstractSortWriter<T>
{
public:
    ParallelMergeWriter()
    {
        sorter = new ParallelMergeSorter<T>;
    }

    void Write(const std::vector<T> &sourceVector) override
    {
        sorter->SetVector(sourceVector);

        auto startTime = std::clock();
        sorter->Sort();
        auto time = std::clock() - startTime;

        std::cout << "Parallel Merge Time: " << time << std::endl;
        std::ofstream output("parallel_merge.txt");
        PutVector(sorter->GetVector(), output);
    }

    ~ParallelMergeWriter()
    {
        delete sorter;
    }
};