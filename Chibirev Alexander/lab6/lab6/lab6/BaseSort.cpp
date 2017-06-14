#include "stdafx.h"
#include "BaseSort.h"

CBaseSort::CBaseSort(const std::vector<int>& vec)
    : m_array(vec)
    , m_isParallelEnabled(false)
{
}

void CBaseSort::WaitForMultiplyObjects(std::vector<std::thread>& threads)
{
    std::for_each(threads.begin(), threads.end(), [](std::thread& thread) { thread.join(); });
}


void CBaseSort::Sort(bool isParallel)
{
    m_isParallelEnabled = isParallel;
    SortArray();
}

std::vector<int> CBaseSort::GetResult() const
{
    return m_array;
}

void CBaseSort::Reset(const std::vector<int>& array)
{
    m_array = array;
}