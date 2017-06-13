using System;
using System.Collections.Generic;

namespace lw7
{
    class Program
    {
        static void Main(string[] args)
        {
            Sorter sorter = new lw7.Sorter();
            int[] a = { 9, 8, 6, 4, 7, 2, 3, 1, 54, 10, 11, 13 };
            List<int> al = new List<int>(a);
            sorter.SortWithThreads(al, 4);
            foreach(int num in al)
            {
                Console.Write(num);
                Console.Write(",");
            }
        }
    }
}
