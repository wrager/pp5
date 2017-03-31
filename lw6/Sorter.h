#pragma once
#include <vector>


class CSorter
{
public:
	CSorter(const std::vector<int> & data)
		:m_data(data)
	{

	}
	virtual void Sort() = 0;
	virtual std::string ToString() = 0;

	std::vector<int> GetData() const;

protected:
	std::vector<int> m_data;
};