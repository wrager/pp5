#pragma once
#include "BaseArraySorter.h"

class CShellArraySorter final
	: public CBaseArraySorter 
{
public:
	static ArraySorterPtr CreateSorter(const SortableArray &vec, bool isParallelMode);
	void Sort()override;

private:
	CShellArraySorter(const SortableArray &vec, bool isParallelMode);

private:
	void ShellIteration(size_t increment);
};