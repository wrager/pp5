#include "stdafx.h"
#include "CShellSort.h"

CShellSort::CShellSort(const std::vector<int>& vec)
    : CBaseSort(vec)
{
}

void CShellSort::SortArray()
{
    auto iterationFunc = [this](size_t end) {
        for (size_t i = 0; i < end; i++)
        {
            ShellIteration(i, end);
        }
    };

    std::vector<std::thread> threads;
    for (size_t end = m_array.size() / 2; end > 0; end /= 2)
    {
        if (m_isParallelEnabled)
        {
            threads.emplace_back(iterationFunc, end);
        }
        else
        {
            iterationFunc(end);
        }
    }

    if (!threads.empty())
    {
        WaitForMultiplyObjects(threads);
    }
}

void CShellSort::ShellIteration(size_t current, size_t half)
{
    for (size_t shifted = half + current, start = shifted; shifted < m_array.size(); shifted += half, start = shifted)
    {
        while (start > current && m_array[start - half] > m_array[start])
        {
            int temp = m_array[start];
            m_array[start] = m_array[start - half];
            m_array[start - half] = temp;
            start -= half;
        }
    }
}