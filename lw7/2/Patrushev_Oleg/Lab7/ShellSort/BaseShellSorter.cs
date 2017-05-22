using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lab7.Abstract;

namespace Lab7.ShellSort
{
    abstract class BaseShellSorter : BaseSorter
    {
        protected BaseShellSorter(List<int> vector)
            : base(vector)
        {

        }

        public override void SortIteration()
        {
            ShellSort();
        }

        protected abstract void ShellSort();
    }
}
