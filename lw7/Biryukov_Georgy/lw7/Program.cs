using System;
using System.Linq;
using System.Diagnostics;
using lw7.ArrayManager;
using lw7.ArrayManipulator;

namespace lw7
{
    class CMainProgram
    {
        static void Main(string[] args)
        {
            Stopwatch sWatch = new Stopwatch();
            int[] kek = CArrayManager.fillArray("kek.txt");

            sWatch.Start();
            CArrayManipulator.sortingProcess(kek);
            sWatch.Stop();
         
            Console.WriteLine(sWatch.ElapsedMilliseconds.ToString() + " ms");

            foreach (int k in kek)
              Console.WriteLine(k);
        }
    }
}
