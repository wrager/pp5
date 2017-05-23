using System;
using System.Collections.Generic;

namespace ArraySorts_Sharp
{
    class Program
    {
        static private Dictionary<String, bool> strBoolCollection;

        static private void FillStrBoolCollection()
        {
            strBoolCollection = new Dictionary<string, bool>();
            strBoolCollection.Add("true", true);
            strBoolCollection.Add("false", false);
        }

        private enum SortingType
        {
            SHELL,
            MERGE
        }

        static private IArraySorter StartSort(List<int> srcArray, bool isParallelMode, SortingType sortingType)
        {
            double elapsedTimeInMs = 0;
            IArraySorter sorter = null;
            switch (sortingType)
            {
                case SortingType.SHELL:
                    sorter = ShellArraySorter.CreateSorter(srcArray, isParallelMode);
                    elapsedTimeInMs = Utils.NotifyExecutionTime(() => sorter.Sort());
                    Console.WriteLine(elapsedTimeInMs);
                    break;
                case SortingType.MERGE:
                    sorter = MergeArraySorter.CreateSorter(srcArray, isParallelMode);
                    elapsedTimeInMs = Utils.NotifyExecutionTime(() => sorter.Sort());
                    break;
            }
            Console.WriteLine("Elapsed time: " + elapsedTimeInMs + "ms");
            return sorter;
        }

        static void Main(string[] args)
        {
            if (args.Length < 2)
            {
                Console.WriteLine("Invalid arguments count");
            }
            else
            {
                try
                {
                    FillStrBoolCollection();

                    List<int> src = Utils.ReadFileToVec(args[0]);
                    bool isParallel = strBoolCollection[args[1]];

                    Console.WriteLine("Merge Sort with paralleling enabled: " + args[1]);
                    StartSort(src, isParallel, SortingType.MERGE);

                    Console.WriteLine("Shell Sort with paralleling enabled: " + args[1]);
                    StartSort(src, isParallel, SortingType.SHELL);
                }
                catch (Exception ex)
                {
                    Console.WriteLine(ex.ToString());
                }
            }
        }
    }
}
