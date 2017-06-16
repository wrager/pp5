using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SortProject.Sorter.ShellSorter
{
    public abstract class AbstractShellSorter<T> : AbstractSorter<T> where T : IComparable
    {
        protected void SortByIntervals( int gap, int start )
        {
            for ( int i = start; i < Lst.Count; i += gap )
            {
                for ( int j = start; j < i; j += gap )
                {
                    if ( Lst[ i ].CompareTo(Lst[ j ]) < 0 )
                    {
                        CycleShift( i, j, gap );
                        continue;
                    }
                }
            }
        }

        protected void CycleShift( int from, int to, int gap )
        {
            var t = Lst[ from ];
            for ( int i = from; i > to; i -= gap )
            {
                Lst[ i ] = Lst[ i - gap ];
            }
            Lst[ to ] = t;
        }
    }
}
