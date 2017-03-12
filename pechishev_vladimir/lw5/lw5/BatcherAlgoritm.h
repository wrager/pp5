#pragma once
#include "stdafx.h"

class CBatcherAlgoritm
{
public:
	CBatcherAlgoritm();
	void SortArray(Array const & arr);
	Array GetSortedArray() const;
private:

private:
	Array m_array;
};

