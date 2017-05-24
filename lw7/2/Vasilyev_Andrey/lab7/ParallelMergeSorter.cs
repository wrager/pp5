using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace lab7
{
    public class CParallelMergeSorter : CSimpleMergeSorter
    {
        private double m_threadsCount;

        public CParallelMergeSorter(List<int> data) : base(data)
        {
            m_threadsCount = Environment.ProcessorCount;
        }

        public override void Sort()
        {
            helper = new List<int>(m_data.Count);
            ParallelSort(0, m_data.Count - 1, 0);
        }

        public override string ToString()
        {
            return "ParallelMergeSorter";
        }

        private void ParallelSort(int low, int high, int level)
        {
            ++level;
            if (low < high)
            {
                int minimalThreadCreatingLevel = (int)Math.Log(m_threadsCount, 2);
                if (level <= minimalThreadCreatingLevel)
                {
                    int middle = low + (high - low) / 2;
                    Thread thLeft = new Thread(() => ParallelSort(low, middle, level));
                    thLeft.Start();
                    Thread thRight = new Thread(() => ParallelSort(middle + 1, high, level));
                    thRight.Start();

                    thLeft.Join();
                    thRight.Join();

                    Merge(low, middle, high);
                }
                else
                {
                    MergeSort(low, high);
                }
            }
        }
    }
}
