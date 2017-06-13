using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lab7.MergeSort;
using Lab7.ShellSort;

namespace Lab7
{
    class Program
    {
        static void OutputWorkTime(Action callback)
        {
            var watch = System.Diagnostics.Stopwatch.StartNew();
            callback();
            watch.Stop();
            Console.WriteLine(watch.ElapsedMilliseconds);
        }

        static void Main(string[] args)
        {
            List<int> data = Utils.ReadFile("numbers.txt");

            LinearMergeSorter lms = new LinearMergeSorter(data);
            LinearShellSorter lss = new LinearShellSorter(data);
            ParallelMergeSorter pms = new ParallelMergeSorter(data);
            ParallelShellSorter pss = new ParallelShellSorter(data);

            OutputWorkTime(() => lms.Sort());
            OutputWorkTime(() => lss.Sort());
            OutputWorkTime(() => pms.Sort());
            OutputWorkTime(() => pss.Sort());

            List<int> result1 = lms.GetData();
            List<int> result2 = lss.GetData();
            List<int> result3 = pms.GetData();
            List<int> result4 = pss.GetData();
        }
    }
}
