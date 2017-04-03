#include "stdafx.h"
#include "MergeSortCalculator.h"

CMergeSortCalculator::CMergeSortCalculator(const std::vector<int>& vec)
    : m_array(vec)
    , m_isParallelEnabled(false)
{
}

void CMergeSortCalculator::Sort(bool isParallel)
{
    m_isParallelEnabled = isParallel;
    StartSort(0, m_array.size() - 1);
}

std::vector<int> CMergeSortCalculator::GetResult() const
{
    return m_array;
}

void CMergeSortCalculator::Reset(const std::vector<int>& array)
{
    m_array = array;
}

void CMergeSortCalculator::StartSort(size_t left, size_t right)
{
    if (right > left)
    {
        size_t middle = (left + right) / 2;
        if (m_isParallelEnabled && (right - left + 1 == m_array.size() / (std::thread::hardware_concurrency())))
        {
            std::vector<std::thread> threads;
            threads.emplace_back(&CMergeSortCalculator::StartSort, this, left, middle);
            threads.emplace_back(&CMergeSortCalculator::StartSort, this, middle + 1, right);
            WaitForMultiplyObjects(threads);
        }
        else
        {
            StartSort(left, middle);
            StartSort(middle + 1, right);
        }
        Merge(left, middle, right);
    }
}

void CMergeSortCalculator::Merge(size_t leftStart, size_t mid, size_t rightEnd)
{
    size_t leftEnd = leftStart;
    size_t rightStart = mid + 1;

    std::vector<int> sorted(rightEnd - leftStart + 1);
    int cur = 0;

    while (leftEnd <= mid && rightStart <= rightEnd)
    {
        if (m_array[leftEnd] <= m_array[rightStart])
        {
            sorted[cur++] = m_array[leftEnd++];
        }
        else
        {
            sorted[cur++] = m_array[rightStart++];
        }
    }

    while (leftEnd <= mid)
    {
        sorted[cur++] = m_array[leftEnd++];
    }
    while (rightStart <= rightEnd)
    {
        sorted[cur++] = m_array[rightStart++];
    }

    while (--cur >= 0)
    {
        m_array[leftStart + cur] = sorted[cur];
    }
}

void CMergeSortCalculator::WaitForMultiplyObjects(std::vector<std::thread>& threads)
{
    std::for_each(threads.begin(), threads.end(), [](std::thread& thread) { thread.join(); });
}
