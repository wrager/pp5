#pragma once
#include <vector>
#include "IBatherSort.h"

class CBatcherSort : public IBatherSort
{
public:
	CBatcherSort(const std::vector<int>& inputMass);
	std::vector<int> GetMass() const;
	~CBatcherSort();

protected:
	void OddEvenMerge(int leftOperand, int length, int rightOperand);
	void Compare(int i, int j);
	std::vector<int> m_mass;
};

