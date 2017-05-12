#pragma once
#include "AbstractSorter.h"
#include <algorithm>

template <class T>
class AbstractMergeSorter : public AbstractSorter<T>
{
protected:
    virtual std::vector<T> SortParts(const std::vector<T> &source)
    {
        if (source.size() < 2)
        {
            return source;
        }

        //делим на 2 части
        int halfSize = source.size() / 2;
        std::vector<T> left(halfSize);
        std::vector<T> right(source.size() - halfSize);
        std::copy(source.begin(), source.begin() + halfSize, left.begin());
        std::copy(source.begin() + halfSize, source.end(), right.begin());

        //сортируем каждую из них
        left = SortParts(left);
        right = SortParts(right);

        //склеиваем
        return Merge(left, right);
    }

    std::vector<T> Merge(const std::vector<T> &left, const std::vector<T> &right)
    {
        std::vector<T> result(left.size() + right.size());

        std::merge(left.begin(), left.end(), right.begin(), right.end(), result.begin());
        return result;
    }
};
