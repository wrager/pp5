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
            List<int> data = DataReader.ReadFromFile();

            //CSimpleMergeSorter simpleMerge = new CSimpleMergeSorter(data);
            //simpleMerge.Sort();
            CParallelShellSorter sorter = new CParallelShellSorter(data);
            sorter.Sort();
            
            DataWriter.WriteToFile(sorter.Data);
        }
    }
}
