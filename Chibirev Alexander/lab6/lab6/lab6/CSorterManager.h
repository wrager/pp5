#pragma once
#include "ISortCalculator.h"

class CSorterManager
{
public:
    CSorterManager(ISortCalculator & calc, const std::string & filename);
    void Start();

private:
    void SortArray(bool parallel = true);
    void GetDataFromFile(const std::string & fileName);
    void CoutArray(const std::string & message, const std::vector<int> & vec);

    ISortCalculator & m_calc;
    std::vector<int> m_fileVec;
};

