#include "stdafx.h"
#include "MegreSortCalculator.h"

CMegreSortCalculator::CMegreSortCalculator(const std::vector<int>& vec)
    : m_array(vec)
    , m_isParallelEnabled(false)
{
}

void CMegreSortCalculator::Sort(bool isParallel)
{
    m_isParallelEnabled = isParallel;
    StartSort(0, m_array.size());
}

std::vector<int> CMegreSortCalculator::GetResult() const
{
    return m_array;
}

void CMegreSortCalculator::Reset(const std::vector<int>& array)
{
    m_array = array;
}

void CMegreSortCalculator::StartSort(size_t left, size_t right)
{
    size_t length = right - left;

    if (length <= 0)
    {
        return;
    }

    size_t m = (left + right) / 2;

    if (right - left + 1 == m_array.size() / (std::thread::hardware_concurrency()))
    {
        std::cout << "starting thread " << left << " " << right << std::endl;
        std::vector<std::thread> threads;
        threads.emplace_back(&CMegreSortCalculator::StartSort, this, left, m);
        threads.emplace_back(&CMegreSortCalculator::StartSort, this, m + 1, right);

        std::for_each(threads.begin(), threads.end(), [](std::thread& thread) { thread.join(); thread.~thread(); });
    }
    else
    {
        StartSort(left, m);
        StartSort(m + 1, right);
    }

    Merge(left, m, right);
}

void CMegreSortCalculator::Merge(size_t low, size_t mid, size_t high)
{
    size_t left = low;
    size_t right = mid + 1;

    std::vector<int> b(high - low + 1);
    int cur = 0;

    while (left <= mid && right <= high)
    {
        if (m_array[left] <= m_array[right])
        {
            b[cur++] = m_array[left++];
        }
        else
        {
            b[cur++] = m_array[right++];
        }
    }

    while (left <= mid)
    {
        b[cur++] = m_array[left++];
    }
    while (right <= high)
    {
        b[cur++] = m_array[right++];
    }
    cur--;
    while (cur >= 0)
    {
        m_array[low + cur] = b[cur];
        cur--;
    }
}
