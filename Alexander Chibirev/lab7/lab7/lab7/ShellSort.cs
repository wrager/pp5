using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace lab7
{
    class ShellSort : BaseSort
    {
        public ShellSort() : base()
        {
        }

        private void IterationFunc(object endObj)
        {
            int end = (int)endObj;
            for (int i = 0; i < end; i++)
            {
                ShellIteration(i, end);
            }
        }

        protected override void SortArray()
        {
            List<Thread> tasks = new List<Thread>();
            for (int end = m_array.Count / 2; end > 0; end /= 2)
            {
                if (m_isParallelEnabled)
                {
                    Thread th = new Thread(new ParameterizedThreadStart(IterationFunc));
                    th.Start(end);
                    tasks.Add(th);
                }
                else
                {
                    IterationFunc(end);
                }
            }

            if (m_isParallelEnabled)
            {
                foreach (Thread task in tasks)
                {
                    task.Join();
                }
            }
        }

        private void ShellIteration(int current, int half)
        {
            for (int shifted = half + current, start = shifted; shifted < m_array.Count; shifted += half, start = shifted)
            {
                while (start > current && m_array[start - half] > m_array[start])
                {
                    int temp = m_array[start];
                    m_array[start] = m_array[start - half];
                    m_array[start - half] = temp;
                    start -= half;
                }
            }
        }
    }
}
