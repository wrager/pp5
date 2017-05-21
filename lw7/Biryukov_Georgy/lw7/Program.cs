using System;
using System.Linq;
using System.Diagnostics;
using System.Threading.Tasks;

namespace lw7
{
    class CMainProgram
    {
        static void Main(string[] args)
        {
            string path = args[0];
            int[] arrayForSingleThread = CArrayManager.fillArray(path);
            int[] arrayForMultuThread = CArrayManager.fillArray(path);

            Stopwatch sWatch = new Stopwatch();
            Stopwatch sWatch2 = new Stopwatch();

            sWatch.Start();
            CArrayManipulator.sortingProcess(arrayForSingleThread);
            sWatch.Stop();
            sWatch2.Start();
            CArrayManipulator.sortingProcessParallel(arrayForMultuThread);
            sWatch2.Stop();

      /*      foreach (int k in arrayForSingleThread)
                Console.WriteLine(k);*/

            Console.WriteLine("One thread " + sWatch.ElapsedMilliseconds.ToString() + " ms");
            Console.WriteLine("Multithread " + sWatch2.ElapsedMilliseconds.ToString() + " ms");                
        }
    }
}
