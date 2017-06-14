#pragma once
class Sorter
{
public:
	static std::vector<int> MergeSort(std::vector<std::vector<int>> const& vec);
private:
	static std::vector<int> MergeVectors(std::vector<int> const& vec1, std::vector<int> const& vec2);

};

