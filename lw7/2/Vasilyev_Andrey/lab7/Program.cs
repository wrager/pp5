using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace lab7
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
            List<int> data = DataReader.ReadFromFile("input1.txt");

            SimpleMergeSorter sms = new SimpleMergeSorter(data);
            SimpleShellSorter sss = new SimpleShellSorter(data);
            ParallelMergeSorter pms = new ParallelMergeSorter(data);
            ParallelShellSorter pss = new ParallelShellSorter(data);

            OutputWorkTime(() => sms.Sort());
            OutputWorkTime(() => sss.Sort());
            OutputWorkTime(() => pms.Sort());
            OutputWorkTime(() => pss.Sort());
            DataWriter.WriteToFile(pss.Data);
            Debug.WriteLine("");
        }
    }
}
