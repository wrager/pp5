#include "stdafx.h"
#include "CSorterManager.h"

CSorterManager::CSorterManager(ISortCalculator & calc, const std::string & filename)
    : m_calc(calc)
{
    GetDataFromFile(filename);
}

void CSorterManager::Start()
{  
    SortArray(false);
    SortArray();
}

void CSorterManager::GetDataFromFile(const std::string & fileName)
{
    std::ifstream file(fileName);
    int elem;
    while (!file.eof())
    {
        file >> elem;
        m_fileVec.push_back(elem);
    }
}

void CSorterManager::CoutArray(const std::string & message, const std::vector<int>& vec)
{
    std::cout << message << std::endl;
}

void CSorterManager::SortArray(bool parallel)
{
    m_calc.Reset(m_fileVec);

    clock_t begin = clock();
    m_calc.Sort(parallel);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    CoutArray("Elapsed time: " + std::to_string(elapsed_secs) + ". Sorted", m_calc.GetResult());
}
