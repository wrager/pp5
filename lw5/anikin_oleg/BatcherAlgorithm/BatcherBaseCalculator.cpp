#include "stdafx.h"
#include "BatcherBaseCalculator.h"

CBatcherBaseCalculator::CBatcherBaseCalculator(const std::vector<int>& vec)
    : m_vec(vec)
{}

void CBatcherBaseCalculator::Sort(bool isParallel)
{
    m_isParallelEnabled = isParallel;
    StartSort(0, m_vec.size());
}

std::vector<int> CBatcherBaseCalculator::GetResult()
{
    return m_vec;
}

void CBatcherBaseCalculator::Reset(const std::vector<int> & vec)
{
    m_vec = vec;
}

void CBatcherBaseCalculator::Merge(size_t left, size_t size, size_t right)
{
    size_t mergeRange = right * 2;
    if (mergeRange < size)
    {
        Merge(left, size, mergeRange);
        Merge(left + right, size, mergeRange);
        for (size_t i = left + right; i + right < left + size; i += mergeRange)
        {
            Compare(m_vec[i], m_vec[i + right]);
        }
    }
    else
    {
        Compare(m_vec[left], m_vec[left + right]);
    }
}

void CBatcherBaseCalculator::Compare(int & left, int & right)
{
    if (left > right)
    {
        std::swap(left, right);
    }
}

void CBatcherBaseCalculator::StartSort(size_t left, size_t right)
{
    if (right > 1)
    {
        size_t m = right / 2;

#pragma omp parallel sections if(m_isParallelEnabled)
        {
#pragma omp section
            StartSort(left, m);
#pragma omp section
            StartSort(left + m, m);
        }
        Merge(left, right, 1);
    }
}
