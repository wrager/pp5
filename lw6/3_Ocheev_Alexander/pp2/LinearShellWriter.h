#pragma once
#include "AbstractSortWriter.h"
#include "LinearShellSorter.h"

template <class T>
class LinearShellWriter : public AbstractSortWriter<T>
{
public:
    LinearShellWriter()
    {
        sorter = new LinearShellSorter<T>;
    }

    void Write(const std::vector<T> &sourceVector) override
    {
        sorter->SetVector(sourceVector);

        auto startTime = std::clock();
        sorter->Sort();
        auto time = std::clock() - startTime;

        std::cout << "Linear Shell Time: " << time << std::endl;
        std::ofstream output("linear_shell.txt");
        PutVector(sorter->GetVector(), output);
    }

    ~LinearShellWriter()
    {
        delete sorter;
    }
};