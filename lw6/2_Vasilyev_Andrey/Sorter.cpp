#include "Sorter.h"

CSorter::CSorter(const std::vector<int> & data)
	:m_data(data)
{

}

void CSorter::SetData(const std::vector<int> & data)
{
	m_data = data;
}

std::vector<int> CSorter::GetData() const
{
	return m_data;
}