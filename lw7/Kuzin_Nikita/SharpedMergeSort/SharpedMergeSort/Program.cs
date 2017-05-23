using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

class Program
{
    static void Main(string[] args)
    {
        if (args.Length != 2)
        {
            Console.WriteLine("Hint: input.txt output.txt");
            return;
        }

        CSimpleMergeSort simpleMerge = new CSimpleMergeSort(args[0], args[1]);
        simpleMerge.Execute();
    }
}
