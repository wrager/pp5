using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab7
{
    class Program
    {
      
        static void Main(string[] args)
        {
       
            try
            {
                Console.WriteLine("Merge sort: ");
                ISortCalculator mergeSort = new MergeSort();
                SortManager mergeSorter = new SortManager(ref mergeSort, "data.txt");
                mergeSorter.Start();

                Console.WriteLine("Shell sort: ");
                ISortCalculator shellSort = new ShellSort();
                SortManager shellSorter = new SortManager(ref shellSort, "data.txt");
                shellSorter.Start();
            }
            catch (Exception except)
            {
                Console.WriteLine(except.ToString());
            }
        }
    }
}
