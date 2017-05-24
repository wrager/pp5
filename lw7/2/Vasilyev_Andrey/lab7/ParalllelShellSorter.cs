using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace lab7
{
    public class CParallelShellSorter : CSimpleShellSorter
    {
        private int m_threadsCount;

        public CParallelShellSorter(List<int> data) : base(data)
        {
            m_threadsCount = Environment.ProcessorCount;
        }

        public override void Sort()
        {
            int n = m_data.Count;
            for (int h = n; h > 0; h /= 2)
            {
                List<Thread> activeThreads = new List<Thread>();
                int t;
                int numberOfElementsPerThread = (int)Math.Floor(((float)(n - h)) / m_threadsCount);

                for (int i = h; i < n; i += numberOfElementsPerThread)
                {
                    activeThreads.Add(new Thread(() => ParallelSort(h, n, i, numberOfElementsPerThread)));
                    activeThreads.Last().Start();
                }
                for (int z = 0; z < activeThreads.Count; ++z)
                {
                    activeThreads[z].Join();
                }
            }

        }

        void ParallelSort(int h, int n, int i, int nElements)
        {
            for (int currentItemId = i; currentItemId < n && currentItemId - i < nElements; ++currentItemId)
            {
                int t = m_data[currentItemId];
                int j;
                for (j = currentItemId; j >= h && t < m_data[j - h]; j -= h)
                {
                    m_data[j] = m_data[j - h];
                }
                m_data[j] = t;
            }
        }

        public override string ToString()
        {
            return "ParallelShellSorter";
        }
    }
}
