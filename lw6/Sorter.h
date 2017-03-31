#pragma once
#include <vector>


class CSorter
{
public:
	CSorter(const std::vector<int> & data);
	std::vector<int> GetData() const;

public:
	virtual void Sort() = 0;
	virtual std::string ToString() = 0;

protected:
	std::vector<int> m_data;
};