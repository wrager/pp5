#pragma once

class IArraySorter;

using ArraySorterPtr = std::unique_ptr<IArraySorter>;
using SortableArray = std::vector<int>;