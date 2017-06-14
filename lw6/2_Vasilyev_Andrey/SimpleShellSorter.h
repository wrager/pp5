#pragma once
#include <vector>
#include "Sorter.h"

class CSimpleShellSorter: public CSorter
{
public:
	CSimpleShellSorter() = default;
	CSimpleShellSorter(const std::vector<int> & data);

public:
	void Sort() override;
	std::string ToString() override;
};