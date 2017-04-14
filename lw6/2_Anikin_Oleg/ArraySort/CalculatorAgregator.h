#pragma once
#include "ISortCalculator.h"

class CCalculatorAggregator
{
public:
    CCalculatorAggregator(ISortCalculator & calc, const std::string & filename);
    void Start();

private:
    void SortArray(bool parallel = true);
    void ReadVectorFromFile(const std::string & fileName);
    void CoutArray(const std::string & message, const std::vector<int> & vec);

    ISortCalculator & m_calc;
    std::vector<int> m_fileVec;
};

