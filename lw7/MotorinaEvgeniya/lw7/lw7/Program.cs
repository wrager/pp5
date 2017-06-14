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
            ShellSorter shellSorter = new lw7.ShellSorter();
            List<int> arr = FileReader.fillArray("../../input.txt");

            Stopwatch stopWatch = new Stopwatch();
            stopWatch.Start();
            sorter.SortWithThreads(arr, 4);
            stopWatch.Stop();
            Console.Write("Merge sort with threads: ");
            Console.Write(stopWatch.Elapsed);
            Console.WriteLine();

            stopWatch.Reset();
            stopWatch.Start();
            sorter.MergeSort(arr);
            stopWatch.Stop();
            Console.Write("Merge sort: ");
            Console.Write(stopWatch.Elapsed);
            Console.WriteLine();

            stopWatch.Reset();
            stopWatch.Start();
            shellSorter.ShellSortWithThreads(arr);
            stopWatch.Stop();
            Console.Write("Shell sort with threads: ");
            Console.Write(stopWatch.Elapsed);
            Console.WriteLine();

            stopWatch.Reset();
            stopWatch.Start();
            shellSorter.ShellSort(arr);
            stopWatch.Stop();
            Console.Write("Shell sort: ");
            Console.Write(stopWatch.Elapsed);
            Console.WriteLine();
        }
    }
}
