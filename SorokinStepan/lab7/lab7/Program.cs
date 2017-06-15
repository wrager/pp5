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
            List<List<int>> arr = ArrWriter.fillArray("input.txt");
            lab7.Sorter sorter = new lab7.Sorter();
            sorter.SetThreadCount(4);
            sorter.SetArray(arr);
            List<int> result = sorter.StartSort();
        }
    }
}
