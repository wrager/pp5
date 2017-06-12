using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab7
{
    class MergeSort : BaseSort
    {

        public MergeSort() : base()
        {
            
        }

        protected override void SortArray()
        {
            StartSort(0, m_array.Count - 1);
        }

        private void StartSort(int left, int right)
        {
            if (right > left)
            {
                int middle = (left + right) / 2;
                if (m_isParallelEnabled && (right - left + 1 == m_array.Count / (Environment.ProcessorCount)))
                {
                    Task th1 = Task.Factory.StartNew(() => StartSort(left, middle));
                    Task th2 = Task.Factory.StartNew(() => StartSort(middle + 1, right));
                    Task.WaitAll(th1, th2);
                }
                else
                {
                    StartSort(left, middle);
                    StartSort(middle + 1, right);
                }
                Merge(left, middle, right);
            }
        }

        private void Merge(int leftStart, int mid, int rightEnd)
        {
            int leftEnd = leftStart;
            int rightStart = mid + 1;

            List<int> sorted = new List<int>(new int[rightEnd - leftStart + 1]);
            int cur = 0;

            while (leftEnd <= mid && rightStart <= rightEnd)
            {
                if (m_array[leftEnd] <= m_array[rightStart])
                {
                    sorted[cur++] = m_array[leftEnd++];
                }
                else
                {
                    sorted[cur++] = m_array[rightStart++];
                }
            }

            while (leftEnd <= mid)
            {
                sorted[cur++] = m_array[leftEnd++];
            }
            while (rightStart <= rightEnd)
            {
                sorted[cur++] = m_array[rightStart++];
            }

            while (--cur >= 0)
            {
                m_array[leftStart + cur] = sorted[cur];
            }
        }
    }
}
