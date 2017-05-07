#pragma once
#include "AbstractSortWriter.h"
#include "ParallelShellSorter.h"

template <class T>
class ParallelShellWriter : public AbstractSortWriter<T>
{
public:
    void Write(const std::vector<T> &sourceVector) override
    {
        auto sorter = ParallelShellSorter<T>();
        sorter.SetVector(sourceVector);

        auto startTime = std::clock();
        sorter.Sort();
        auto time = std::clock() - startTime;

        std::cout << "Parallel Shell Time: " << time << std::endl;
        std::ofstream output("parallel_shell.txt");
        PutVector(sorter.GetVector(), output);
    }
};