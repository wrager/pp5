#pragma once
#include "AbstractSorter.h"
#include <algorithm>

template <class T>
class LinearMergeSorter : public AbstractSorter<T>
{
public:
    void Sort() override
    {
        vector = SortParts(vector);
    }

private:
    std::vector<T> SortParts(const std::vector<T> &source)
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
        std::vector<T> result;

        auto leftCursor = left.begin();
        auto rightCursor = right.begin();

        while (leftCursor != left.end() && rightCursor != right.end())
        {
            if (*leftCursor < *rightCursor)
            {
                result.push_back(*(leftCursor++));
            }
            else
            {
                result.push_back(*(rightCursor++));
            }
        }

        std::for_each(leftCursor, left.end(), [&](const T &n) {
            result.push_back(n);
        });
        std::for_each(rightCursor, right.end(), [&](const T &n) {
            result.push_back(n);
        });

        return result;
    }
};