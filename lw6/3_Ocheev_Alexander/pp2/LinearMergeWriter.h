#pragma once
#include "AbstractSortWriter.h"
#include "LinearMergeSorter.h"

template <class T>
class LinearMergerWriter : public AbstractSortWriter<T>
{
public:
    LinearMergerWriter()
    {
        sorter = new LinearMergeSorter<T>();
    }

    void Write(const std::vector<T> &sourceVector) override
    {
        sorter->SetVector(sourceVector);

        auto startTime = std::clock();
        sorter->Sort();
        auto time = std::clock() - startTime;

        std::cout << "Linear Merge Time: " << time << std::endl;
        std::ofstream output("linear_merge.txt");
        PutVector(sorter->GetVector(), output);
    }

    ~LinearMergerWriter()
    {
        delete sorter;
    }
};