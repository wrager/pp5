using System;
using System.Linq;
using System.Diagnostics;
using System.Threading.Tasks;
using System.IO;

namespace lw7
{
    class CMainProgram
    {
        static void Main(string[] args)
        {
            string path = args[0];
            int[] arrayForSingleThread = CArrayManager.fillArray(path);
            int[] arrayForMultiThread = arrayForSingleThread;

            Stopwatch sWatch = new Stopwatch();
            Stopwatch sWatch2 = new Stopwatch();

            sWatch.Start();
            CArrayManipulator.sortingProcess(arrayForSingleThread);
            sWatch.Stop();
            sWatch2.Start();
            CArrayManipulator.sortingProcessParallel(arrayForMultiThread);
            sWatch2.Stop();

            CArrayManager.output(arrayForMultiThread);
            Console.WriteLine("One thread " + sWatch.ElapsedMilliseconds.ToString() + " ms");
            Console.WriteLine("Multithread " + sWatch2.ElapsedMilliseconds.ToString() + " ms");                
        }
    }
}
