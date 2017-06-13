#pragma once
#include "IArraySorter.h"
#include "ThreadPool.h"

class CBaseArraySorter
	: public IArraySorter
{
public:
	void Sort() override;
	SortableArray GetResult()const final;

protected:
	CBaseArraySorter(const SortableArray &vec, bool isParallelMode);

	std::vector<int> m_result;
	bool m_isParallelMode;
};