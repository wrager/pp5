using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lw7
{
    class ShellSorter
    {
        private List<int> m_array;

        private void Sort(int increment)
        {
            int j = 0;
            int temp = 0;
            for (int i = increment; i < m_array.Count(); i++)
            {
                temp = m_array[i];
                for (j = i; j >= increment && temp < m_array[j - increment]; j -= increment)
                {
                    m_array[j] = m_array[j - increment];
                }
                m_array[j] = temp;
            }
        }

        public void ShellSortWithThreads(List<int> array)
        {
            m_array = array;
            ThreadPool threadPool = new ThreadPool();
            for (int i = m_array.Count() / 2; i > 0; i /= 2)
            {
                threadPool.AddThread(Task.Factory.StartNew(() => Sort(i)));
            }
            threadPool.WaitThread();
            array = m_array;
        }

        public void ShellSort(List<int> array)
        {
            m_array = array;
            for (int i = m_array.Count() / 2; i > 0; i /= 2)
            {
                Sort(i);
            }
            array = m_array;
        }

    }
}
