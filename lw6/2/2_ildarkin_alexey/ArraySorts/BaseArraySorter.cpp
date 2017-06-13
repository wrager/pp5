#include "stdafx.h"
#include "BaseArraySorter.h"

CBaseArraySorter::CBaseArraySorter(const SortableArray &vec, bool isParallelMode)
	: m_result(vec)
	, m_isParallelMode(isParallelMode)
{
}

void CBaseArraySorter::Sort()
{
	//Implement in inherited classes
}

SortableArray CBaseArraySorter::GetResult() const
{
	return m_result;
}
