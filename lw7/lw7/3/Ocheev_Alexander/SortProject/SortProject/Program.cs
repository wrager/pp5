using SortProject.Sorter;
using SortProject.Sorter.MergerSorter;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SortProject
{
    class Program
    {
        static void Main( string[] args )
        {
            var handler = new FileHandler();
            handler.ReadInput( args[ 0 ] );

            handler.Sorter = new LinearMergeSorter<int>();
            handler.Run( "Linear", "linear_merge.txt" );

            handler.Sorter = new ParallelMergeSorter<int>();
            handler.Run( "Parallel", "parallel_merge.txt" );
        }
    }
}
