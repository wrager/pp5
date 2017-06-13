using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace lw7
{
    class Program
    {
        static void Main(string[] args)
        {
            Sorter sorter = new lw7.Sorter();
            int[] a = { 9, 8, 6, 4, 7, 2, 3, 1, 54, 10, 11, 13 };
            List<int> al = new List<int>(a);
            Stopwatch stopWatch = new Stopwatch();
            stopWatch.Start();
            sorter.SortWithThreads(al, 4);
            stopWatch.Stop();
            Console.Write(stopWatch.Elapsed);
        }
    }
}
