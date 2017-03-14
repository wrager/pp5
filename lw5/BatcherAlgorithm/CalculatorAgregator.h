#pragma once
#include "IBatcherCalculator.h"

class CCalculatorAggregator
{
public:
    CCalculatorAggregator(IBatcherCalculator & calc, const std::string & filename);
    void Start();

private:
    void SortArray(bool parallel = true);
    void ReadVectorFromFile(const std::string & fileName);
    void CoutArray(const std::string & message, const std::vector<int> & vec);

    IBatcherCalculator & m_calc;
    std::vector<int> m_fileVec;
};

