using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lw7
{
    class Sorter
    {
        public List<int> m_array = new List<int>();

        public void MergeSort(List<int> array)
        {
            m_array = array;
            Sort(0, m_array.Count() - 1);
            array = m_array;
        }

        public void SortWithThreads(List<int> array, int threadCount)
        {
            m_array = array;
            StartThreads(threadCount);
            Sort(0, m_array.Count() - 1);
            array = m_array;

        }

	void Sort(int b, int e)
        {
            int begin = b;
            int end = e;

            if (begin != end)
            {
                if (end - begin != 1)
                {
                    int half = (end + begin) / 2;
                    Sort(begin, half);
                    Sort(half + 1, end);
                    int[] buf = new int[m_array.Count()];
                    int xl = begin;
                    int xr = half + 1;
                    int cur = 0;
                    while (end - begin + 1 != cur)
                    {
                        if (xl > half)
                        {
                            buf[cur++] = m_array[xr++];
                        }
                        else if (xr > end)
                        {
                            buf[cur++] = m_array[xl++];
                        }
                        else if (m_array[xl] > m_array[xr])
                        {
                            buf[cur++] = m_array[xr++];
                        }
                        else
                        {
                            buf[cur++] = m_array[xl++];
                        }
                    }
                    for (int i = 0; i < cur; i++)
                    {
                        m_array[i + begin] = buf[i];
                    }
                }
                else if (m_array[end] < m_array[begin])
                {
                    int temp = m_array[end];
                    m_array[end] = m_array[begin];
                    m_array[begin] = temp;
                }
            }
        }

    void StartThreads(int count)
        {
            ThreadPool threadPool = new ThreadPool();
            int size = m_array.Count();
            int block = (int)Math.Floor((double)size / count);
            int currentPos = 0;
            for (int threadId = 0; threadId < count && currentPos < size; ++threadId)
            {
                int end = Math.Min(size - 1, currentPos + block);
                int begin = currentPos;
                threadPool.AddThread(Task.Factory.StartNew(() => Sort(begin, end)));
                currentPos += block + 1;

            }
            threadPool.WaitThread();
        }
    }
}
