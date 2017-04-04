#include "stdafx.h"
#include "BaseSortCalculator.h"

CBaseSortCalculator::CBaseSortCalculator(const std::vector<int>& vec)
    : m_array(vec)
    , m_isParallelEnabled(false)
{
}

void CBaseSortCalculator::WaitForMultiplyObjects(std::vector<std::thread>& threads)
{
    std::for_each(threads.begin(), threads.end(), [](std::thread& thread) { thread.join(); });
}


void CBaseSortCalculator::Sort(bool isParallel)
{
    m_isParallelEnabled = isParallel;
}

std::vector<int> CBaseSortCalculator::GetResult() const
{
    return m_array;
}

void CBaseSortCalculator::Reset(const std::vector<int>& array)
{
    m_array = array;
}