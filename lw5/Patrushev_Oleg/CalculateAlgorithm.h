#pragma once

template <typename T>
class CBatchersMergeSorter
{

public:

	CBatchersMergeSorter(const std::vector<T>& vec)
		: m_vec(vec)
	{

	}

	void Sort()
	{
		BatchersMergeSort(0, m_vec.size());
	}

	std::vector<T> GetResultVector()
	{
		return m_vec;
	}

protected:

	virtual void BatchersMergeSort(size_t left, size_t right) = 0;

	void BatchersMerge(size_t left, size_t size, size_t right)
	{
		size_t m = right * 2;
		if (m < size)
		{
			BatchersMerge(left, size, m);  
			BatchersMerge(left + right, size, m);
			for (size_t i = left + right; i + right < left + size; i += m)
				Compare(i, i + right);
		}
		else
		{
			Compare(left, left + right);
		}
	}

	void Compare(size_t i, size_t j)
	{
		if (m_vec[i] > m_vec[j])
		{
			Exchange(i, j);
		}
	}

	void Exchange(size_t i, size_t j)
	{
		size_t t = m_vec[i];
		m_vec[i] = m_vec[j];
		m_vec[j] = t;
	}

protected:
	std::vector<T> m_vec;
};
