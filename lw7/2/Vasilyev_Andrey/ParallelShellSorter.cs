using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace lab7
{
    public class ParallelShellSorter: Sorter
    {
        private int _threadsCount;

        public ParallelShellSorter(List<int> data)
            : base(data)
        {
            _threadsCount = Environment.ProcessorCount;
        }

        public override void Sort()
        {
            int h;
            int n = Data.Count;
            for (h = n; h > 0; h /= 2)
            {
                List<Thread> activeThreads = new List<Thread>();
                int numberOfElementsPerThread = (int)Math.Ceiling((double)((n - h) / _threadsCount));

                for (int i = h; i < n; i += numberOfElementsPerThread)
                {
                    activeThreads.Add(new Thread(delegate() { ParallelSort(h, n, i, numberOfElementsPerThread); }));
                    activeThreads.Last().Start();
                }
                activeThreads.ForEach(thread => thread.Join());
            }
        }

        public override string ToString()
        {
            return "Parallel shellSorter";
        }

        private void ParallelSort(int h, int n, int i, int nElements)
        {
            for (int currentItemId = i; currentItemId < n && currentItemId - i < nElements; ++currentItemId)
            {
                int t = Data[currentItemId];
                int j;
                for (j = currentItemId; j >= h && t < Data[j - h]; j -= h)
                {
                    Data[j] = Data[j - h];
                }
                Data[j] = t;
            }
        }
    }
}
