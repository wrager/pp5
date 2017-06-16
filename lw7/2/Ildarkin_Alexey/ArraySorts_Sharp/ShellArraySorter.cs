using System.Collections.Generic;
using System.Threading;

namespace ArraySorts_Sharp
{
    class ShellArraySorter: BaseArraySorter
    {
        public static ShellArraySorter CreateSorter(List<int> src, bool isParallelMode)
        {
            return new ShellArraySorter(src, isParallelMode);
        }

        override public void Sort()
        {
            List<Thread> threads = new List<Thread>();
            for (int increment = _result.Count / 2; increment > 0; increment /= 2)
            {
                if (_isParallelMode)
                {
                    threads.Add(new Thread(delegate () { ShellIteration(increment); }));
                }
                else
                {
                    ShellIteration(increment);
                }
            }
            threads.ForEach(thread => thread.Start());
            threads.ForEach(thread => thread.Join());
        }

        private void ShellIteration(int increment)
        {
            int j = 0;
            for (int i = increment; i < _result.Count; i++)
            {
                int temp = _result[i];
                for (j = i; j >= increment
                    && temp < _result[j - increment]; j -= increment)
                {
                    _result[j] = _result[j - increment];
                }
                _result[j] = temp;
            }
        }

        private ShellArraySorter(List<int> src, bool isParallelMode)
            : base(src, isParallelMode)
        {
        }
    }
}
