using System;
using System.Collections.Generic;
using System.Threading;

namespace ArraySorts_Sharp
{
    class MergeArraySorter: BaseArraySorter
    {
        public static MergeArraySorter CreateSorter(List<int> src, bool isParallelMode)
        {
            return new MergeArraySorter(src, isParallelMode);
        }

        override public void Sort()
        {
            MergeSort(0, _result.Count - 1);
        }
        
        private void MergeSort(int left, int right)
        {
            if (left < right)
            {
                int middle = (left + right) / 2;
                bool hardwareThreadsContextsValid = ((right - left + 1) == (_result.Count / Environment.ProcessorCount));
                if (_isParallelMode && hardwareThreadsContextsValid)
                {
                    List<Thread> threads = new List<Thread>();
                    threads.Add(new Thread(delegate () { MergeSort(left, middle); }));
                    threads.Add(new Thread(delegate () { MergeSort(middle + 1, right); }));
                    threads.ForEach(thread => thread.Start());
                    threads.ForEach(thread => thread.Join());
                }
                else
                {
                    MergeSort(left, middle);
                    MergeSort(middle + 1, right);
                }
                Merge(left, middle, right);
            }
        }

        private void Merge(int left, int middle, int right)
        {
            int start = middle + 1;
            int current = 0;
            int end = left;
            List<int> sortedResult = new List<int>(new int[right - left + 1]);
            
            while (end <= middle && start <= right)
            {
                if (_result[end] <= _result[start])
                {
                    sortedResult[current++] = _result[end++];
                }
                else
                {
                    sortedResult[current++] = _result[start++];
                }
            }
            while (end <= middle || start <= end)
            {
                if (start <= end)
                {
                    sortedResult[current++] = _result[start++];
                }
                else if (end <= middle)
                {
                    sortedResult[current++] = _result[end++];
                }
            }
            while (--current < sortedResult.Count && current >= 0)
            {
                 _result[current + left] = sortedResult[current];
            }
        }

        private MergeArraySorter(List<int> src, bool isParallelMode)
            : base(src, isParallelMode)
        {
        }
    }
}
