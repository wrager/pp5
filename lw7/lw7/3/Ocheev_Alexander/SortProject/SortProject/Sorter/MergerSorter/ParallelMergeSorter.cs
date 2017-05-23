using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace SortProject.Sorter.MergerSorter
{
    public class ParallelMergeSorter<T> : AbstractMergeSorter<T> where T : IComparable
    {
        public ParallelMergeSorter()
        {
            _threadCount = Process.GetCurrentProcess().Threads.Count;
        }

        public override void Sort()
        {
            Parallelize();
        }

        private void Parallelize()
        {
            var threads = new List<Thread>();

            var parts = new List<List<T>>();
            var partLength = Lst.Count / _threadCount;
            for ( int i = 0; i < _threadCount; i++ )
            {
                var currentPart = new List<T>();
                var count = i == _threadCount - 1 ? Lst.Count - partLength * i : partLength;
                currentPart.AddRange( Lst.GetRange( partLength * i, count ) );
                threads.Add( new Thread( delegate () { parts.Add( SortParts( currentPart ) ); } ) );
            }

            foreach ( var th in threads )
            {
                th.Start();
            }
            foreach ( var th in threads )
            {
                th.Join();
            }

            Lst = new List<T>();
            foreach( var part in parts )
            {
                Lst = Merge( Lst, part );
            }
        }

        private int _threadCount;
    }
}
