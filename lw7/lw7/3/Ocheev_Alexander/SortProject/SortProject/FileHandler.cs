using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SortProject.Sorter
{
    public class FileHandler
    {
        public void ReadInput(string inputFile)
        {
            var numbers = File.ReadAllText( inputFile )
                .Split( ' ' )
                .Where( str => str != " " )
                .Select( str => int.Parse( str ) );

            _list = numbers.ToList();
        }

        private void WriteOutput(string outputFile)
        {
            using ( System.IO.StreamWriter file = new System.IO.StreamWriter( outputFile, false ) )
            {
                foreach ( var number in _list )
                {
                    file.Write( number.ToString() + " " );
                }
            }
        }

        public void Run(string text, string outputFile)
        {
            Sorter.Lst = _list;
            Sorter.Sort();

            var watch = System.Diagnostics.Stopwatch.StartNew();
            watch.Stop();

            Sorter.Sort();

            var elapsedMs = watch.ElapsedMilliseconds;

            Console.WriteLine( string.Format( "{0} time: {1}", text, elapsedMs.ToString() ) );
        }

        public AbstractSorter<int> Sorter { set; private get; }

        List<int> _list;
    }
}
