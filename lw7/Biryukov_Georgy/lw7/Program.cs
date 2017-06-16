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
            int[] arrayForMultiThread = CArrayManager.fillArray(path);
            int[] arrayForParallelMerge = CArrayManager.fillArray(path);
            int[] arrayForMerge = CArrayManager.fillArray(path);

            Stopwatch sWatch3 = new Stopwatch();
            Stopwatch sWatch = new Stopwatch();
            Stopwatch sWatch2 = new Stopwatch();
            Stopwatch sWatch4 = new Stopwatch();

            sWatch.Start();
            CArrayManipulator.sortingProcess(arrayForSingleThread);
            sWatch.Stop();

            sWatch2.Start();
            CArrayManipulator.sortingProcessParallel(arrayForMultiThread);
            sWatch2.Stop();

            sWatch3.Start();
            CArrayManipulator.MergeSort(arrayForMerge, 0, arrayForMerge.Length - 1); ;
            sWatch3.Stop();

            sWatch4.Start();
            CArrayManipulator.MergeSortParallel(arrayForParallelMerge, 0, arrayForParallelMerge.Length - 1); ;
            sWatch4.Stop();

            Console.WriteLine("Shell one thread " + sWatch.ElapsedMilliseconds.ToString() + " ms");
            Console.WriteLine("Shell multithread " + sWatch2.ElapsedMilliseconds.ToString() + " ms");
            Console.WriteLine("Merge one thread " + sWatch3.ElapsedMilliseconds.ToString() + " ms");
            Console.WriteLine("Merge multithread " + sWatch4.ElapsedMilliseconds.ToString() + " ms");

            CArrayManager.output(arrayForMerge);

        }
    }
}
