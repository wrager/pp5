#pragma once
class IBatherSort
{
public:
	virtual ~IBatherSort() = default;
	virtual void OddEvenMergeSort(int leftOperand, int length) = 0;
	virtual void Sort() = 0;
};