#pragma once
#include "AbstractSortWriter.h"
#include "ParallelShellSorter.h"

template <class T>
class ParallelShellWriter : public AbstractSortWriter<T>
{
public:
    ParallelShellWriter()
    {
        sorter = new ParallelShellSorter<T>;
    }

    void Write(const std::vector<T> &sourceVector) override
    {
        sorter->SetVector(sourceVector);

        auto startTime = std::clock();
        sorter->Sort();
        auto time = std::clock() - startTime;

        std::cout << "Parallel Shell Time: " << time << std::endl;
        std::ofstream output("parallel_shell.txt");
        PutVector(sorter->GetVector(), output);
    }

    ~ParallelShellWriter()
    {
        delete sorter;
    }
};