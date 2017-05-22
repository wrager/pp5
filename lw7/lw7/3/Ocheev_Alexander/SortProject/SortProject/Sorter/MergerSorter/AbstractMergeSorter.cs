using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SortProject.Sorter.MergerSorter
{
    public abstract class AbstractMergeSorter<T> : AbstractSorter<T> where T : IComparable
    {
        protected List<T> SortParts(List<T> list)
        {
            if ( list.Count < 2 )
            {
                return list;
            }

            var halfSize = list.Count / 2;
            var leftSorted = SortParts( list.GetRange( 0, halfSize ) );
            var rightSorted = SortParts( list.GetRange( halfSize, list.Count - halfSize ) );

            return Merge( leftSorted, rightSorted );
        }

        protected List<T> Merge(List<T> left, List<T> right)
        {
            var result = new List<T>();
            int i = 0, j = 0;
            for (; i < left.Count && j < right.Count;)
            {
                if (left[i].CompareTo(right[j]) < 0)
                {
                    result.Add( left[ i ] );
                    i++;
                }
                else
                {
                    result.Add( right[ j ] );
                    j++;
                }
            }

            if (i < left.Count)
            {
                result.AddRange( left.GetRange( i, left.Count - i ) );
            }
            if (j < right.Count)
            {
                result.AddRange( right.GetRange( j, right.Count - j ) );
            }

            return result;
        }
    }
}
