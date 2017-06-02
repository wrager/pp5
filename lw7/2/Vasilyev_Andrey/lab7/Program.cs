using System;
using System.Collections;
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
            ArrayList d = new ArrayList(data);

            CSorter sorter = new CParallelMergeSorter(d);
            sorter.Sort();
            //CParallelShellSorter sorter = new CParallelShellSorter(data);
            //sorter.Sort();
            
            DataWriter.WriteToFile(sorter.Data);
        }
    }
}
