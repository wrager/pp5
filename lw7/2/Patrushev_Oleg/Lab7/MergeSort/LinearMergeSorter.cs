using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab7.MergeSort
{
    class LinearMergeSorter : BaseMergeSort
    {
        public LinearMergeSorter(List<int> vector)
            : base(vector)
        {
            
        }

        protected override void MergeSort(int p, int r)
        {
            if (p >= r)
            {
                return;
            }

            int q = (p + r) / 2;

            MergeSort(p, q);
            MergeSort(q + 1, r);
            Utils.Merge(ref _vector, p, q, r);
        }
    }
}
