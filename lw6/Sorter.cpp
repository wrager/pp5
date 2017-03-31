#include "Sorter.h"

CSorter::CSorter(const std::vector<int> & data)
	:m_data(data)
{

}

std::vector<int> CSorter::GetData() const
{
	return m_data;
}