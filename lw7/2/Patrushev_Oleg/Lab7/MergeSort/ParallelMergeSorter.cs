using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Lab7.MergeSort
{
    class ParallelMergeSorter : BaseMergeSort
    {
        private int _coresCount;

        public ParallelMergeSorter(List<int> vector)
            : base(vector)
        {
            _coresCount = Environment.ProcessorCount;
        }

        protected override void MergeSort(int l, int r)
        {
            int length = r - l;

            if (length <= 0)
            {
                return;
            }

            int m = (l + r) / 2;

            if (r - l + 1 == _startVectorSize / (_coresCount))
            {
                //Parallel.Invoke(
                //    () => MergeSort(l, m),
                //    () => MergeSort(m + 1, r));

                List<Thread> threads = new List<Thread>();
                threads.Add(new Thread(delegate() { MergeSort(l, m); }));
                threads.Add(new Thread(delegate () { MergeSort(m + 1, r); }));
                threads.ForEach(thread => thread.Start());
                threads.ForEach(thread => thread.Join());
            }
            else
            {
                MergeSort(l, m);
                MergeSort(m + 1, r);
            }

            Utils.Merge(ref _vector, l, m, r);
        }
    }
}
