using Lab7.Abstract;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab7.MergeSort
{
    abstract class BaseMergeSort : BaseSorter
    {
        protected BaseMergeSort(List<int> vector)
            : base(vector)
        {
            
        }

        public override void SortIteration()
        {
            MergeSort(0, _startVectorSize - 1);
        }

        protected abstract void MergeSort(int p, int r);
    }
}
