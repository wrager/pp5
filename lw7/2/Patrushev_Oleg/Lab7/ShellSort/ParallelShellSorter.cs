using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Lab7.ShellSort
{
    class ParallelShellSorter : BaseShellSorter
    {
        List<Thread> _threads;

        public ParallelShellSorter(List<int> vector)
            : base(vector)
        {
            _threads = new List<Thread>();
        }

        protected override void ShellSort()
        {
            for (int h = _vector.Count / 2; h > 0; h = h / 2)
            {
                //Parallel.Invoke(() => ThreadFunction(h));
                _threads.Add(new Thread(delegate () { ThreadFunction(h); }));
                _threads.Last().Start();
            }
            _threads.ForEach(thread => thread.Join());
        }

        private void ThreadFunction(int h)
        {
            for (int i = 0; i < h; i++)
            {
                Utils.InsertSort(ref _vector, i, h);
            }
        }
    }
}
