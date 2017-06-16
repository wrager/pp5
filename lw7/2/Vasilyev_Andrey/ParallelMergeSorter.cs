using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace lab7
{
    public class ParallelMergeSorter: SimpleMergeSorter
    {
        private int _threadsCount;

        public ParallelMergeSorter(List<int> data)
            : base(data)
        {
            _threadsCount = Environment.ProcessorCount;
        }

        public override string ToString()
        {
            return "Parallel mergeSorter";
        }

        public override void Sort()
        {
            helper = new List<int>(new int[Data.Count + 1]);
            ParallelSort(0, Data.Count - 1, 0);
        }

        private void ParallelSort(int low, int high, int level)
        {
            ++level;
            if (low < high)
            {
                int minimalThreadCreatingLevel = (int)Math.Log(_threadsCount, 2);
                if (level <= minimalThreadCreatingLevel)
                {
                    int middle = low + (high - low) / 2;

                    Thread thLeft = new Thread(delegate () { ParallelSort(low, middle, level); });
                    Thread thRight = new Thread(delegate () { ParallelSort(middle + 1, high, level); });
                    thLeft.Start();
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
