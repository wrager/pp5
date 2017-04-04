#pragma once
class CSorter
{
public:
	CSorter();
	~CSorter();

	void MergeSort(std::vector<int> & array, size_t begin, size_t end);

private:
	void Sort(size_t begin, size_t end);
	std::vector<int> m_array;
};

