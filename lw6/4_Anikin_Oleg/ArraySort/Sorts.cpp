#include "stdafx.h"
#include "Sorts.h"

namespace sorts
{

std::vector<int> MergeSort(const std::vector<int> & array, size_t low, size_t mid, size_t high)
{
    size_t left = low;
    size_t right = mid + 1;

    std::vector<int> b(high - low + 1);
    auto result = array;

    int cur = 0;

    while (left <= mid && right <= high)
    {
        if (result[left] <= result[right])
        {
            b[cur++] = result[left++];
        }
        else
        {
            b[cur++] = result[right++];
        }
    }

    while (left <= mid)
    {
        b[cur++] = result[left++];
    }
    while (right <= high)
    {
        b[cur++] = result[right++];
    }
    cur--;
    while (cur >= 0)
    {
        result[low + cur] = b[cur];
        cur--;
    }

    return result;
}

std::vector<int> ShellSort(const std::vector<int> & array, int i, int half)
{
    int temp = 0;
    int j = 0;

    auto result = array;

    for (size_t f = half + i; f < result.size(); f += half)
    {
        j = f;
        while (j > i && result[j - half] > result[j])
        {
            temp = array[j];
            result[j] = result[j - half];
            result[j - half] = result[j];
            j -= half;
        }
    }

    return result;
}

}
