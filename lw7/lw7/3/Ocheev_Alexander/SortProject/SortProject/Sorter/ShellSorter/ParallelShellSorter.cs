using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace SortProject.Sorter.ShellSorter
{
    public class ParallelShellSorter<T> : AbstractShellSorter<T> where T : IComparable
    {
        public override void Sort()
        {
            throw new NotImplementedException();
        }
    }
}
