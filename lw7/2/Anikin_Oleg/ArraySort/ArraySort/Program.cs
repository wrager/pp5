using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArraySort
{
    class Program
    {
        static void Main(string[] args)
        {
                try
                {
                    List<int> emptyList = new List<int>();
                    Console.WriteLine("Merge:");
                    ISortCalculator mergeCalc = new MergeSortCalculator(emptyList);
                    CalculatorAgregator mergeAggregator = new CalculatorAgregator(ref mergeCalc, "fil.txt");
                    mergeAggregator.Start();

                    Console.WriteLine("Shell:");
                    ISortCalculator shellCalc = new ShellSortCalculator(emptyList);
                    CalculatorAgregator shellAggregator = new CalculatorAgregator(ref shellCalc, "fil.txt");
                    shellAggregator.Start();
                }
                catch (Exception except)
                {
                    Console.WriteLine(except.ToString());
                }

            }
    }
}
