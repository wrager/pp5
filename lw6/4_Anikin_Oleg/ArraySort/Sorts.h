#pragma once

namespace sorts
{
std::vector<int> MergeSort(const std::vector<int> & array, size_t low, size_t mid, size_t high);
std::vector<int> ShellSort(const std::vector<int> & array, int i, int half);
}

