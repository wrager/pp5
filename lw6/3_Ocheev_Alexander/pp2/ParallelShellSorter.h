#pragma once
#include "LinearShellSorter.h"
#include <thread>

template <class T>
class ParallelShellSorter : public LinearShellSorter<T>
{
public:
    ParallelShellSorter()
    {
        threadCount = std::thread::hardware_concurrency();
    }

    void Sort() override
    {
        std::vector<std::thread> threads(threadCount);
        int threadCounter = 0;

        for (int gap = vector.size() / 2; gap > 0; gap /= 2)
        {
            int start = 0;
            while (start < gap)
            {
                //attach
                threads[threadCounter] = std::thread(&ParallelShellSorter<T>::SortByIntervals, this, gap, start);

                threadCounter++;
                start++;

                //wait
                if (threadCounter == threadCount)
                {
                    for (auto &th : threads)
                    {
                        th.join();
                    }
                    threadCounter = 0;
                }
            }

            for (auto &th : threads)
            {
                if (th.joinable())
                {
                    th.join();
                }
            }
            threadCounter = 0;
        }
    }

private:
    int threadCount = 2;
};