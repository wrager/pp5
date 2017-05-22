using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SortProject.Sorter.MergerSorter
{
    public class LinearMergeSorter<T> : AbstractMergeSorter<T> where T : IComparable
    {
        public override void Sort()
        {
            _list = SortParts( _list );
        }
    }
}
