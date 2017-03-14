#include "stdafx.h"
#include "CalculatorAgregator.h"
#include <ctime>

CCalculatorAggregator::CCalculatorAggregator(IBatcherCalculator & calc, const std::string & filename)
    : m_calc(calc)
{
    ReadVectorFromFile(filename);
}

void CCalculatorAggregator::Start()
{  
    SortArray(false);
    SortArray();
}

void CCalculatorAggregator::ReadVectorFromFile(const std::string & fileName)
{
    std::ifstream file(fileName);
    int elem;
    while (!file.eof())
    {
        file >> elem;
        m_fileVec.push_back(elem);
    }
}

void CCalculatorAggregator::CoutArray(const std::string & message, const std::vector<int>& vec)
{
    std::cout << message << std::endl;
}

void CCalculatorAggregator::SortArray(bool parallel)
{
    m_calc.Reset(m_fileVec);

    clock_t begin = clock();
    m_calc.Sort(parallel);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    CoutArray("Elapsed time: " + std::to_string(elapsed_secs) + ". Sorted", m_calc.GetResult());
}
