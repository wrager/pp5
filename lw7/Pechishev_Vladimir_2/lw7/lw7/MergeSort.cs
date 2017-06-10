using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Threading;

namespace ArraySort
{
    class CMergeSort
    {
        private List<int> m_array = new List<int>();
        private bool m_parallelMode = false;
        public void Sort(List<int> array, bool isParallel)
        {
            m_array = array;
            m_parallelMode = isParallel;
            MergeSort(0, m_array.Count - 1);
        }

        public List<int> GetSortedArray()
        {
            return m_array;
        }

        private void MergeSort(int left, int right)
        {
            if (left < right)
            {
                int middle = (left + right) / 2;
                bool hardwareThreadsContextsValid = ((right - left + 1) == (m_array.Count / Environment.ProcessorCount));
                if (m_parallelMode && hardwareThreadsContextsValid)
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
                if (m_array[end] <= m_array[start])
                {
                    sortedResult[current++] = m_array[end++];
                }
                else
                {
                    sortedResult[current++] = m_array[start++];
                }
            }
            while (end <= middle || start <= end)
            {
                if (start <= end)
                {
                    sortedResult[current++] = m_array[start++];
                }
                else if (end <= middle)
                {
                    sortedResult[current++] = m_array[end++];
                }
            }
            while (--current < sortedResult.Count && current >= 0)
            {
                m_array[current + left] = sortedResult[current];
            }
        }
    }
}
