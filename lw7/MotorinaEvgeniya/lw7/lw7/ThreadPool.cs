using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lw7
{
    class ThreadPool
    {
        private List<Task> m_threads = new List<Task>();

        public void AddThread(Task task)
        {
            m_threads.Add(task);
        }

        public void WaitThread()
        {
            foreach(Task task in m_threads)
            {
                task.Wait();
            }
        }
    }
}
