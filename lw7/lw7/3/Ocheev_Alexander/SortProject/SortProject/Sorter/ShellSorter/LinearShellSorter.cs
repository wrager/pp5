using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SortProject.Sorter.ShellSorter
{
    public class LinearShellSorter<T> : AbstractShellSorter<T> where T : IComparable
    {
        public override void Sort()
        {
            for ( int gap = Lst.Count / 2; gap > 0; gap /= 2 )
            {
                for ( int start = 0; start < gap; start++ )
                {
                    SortByIntervals( gap, start );
                }
            }
        }
    }
}
