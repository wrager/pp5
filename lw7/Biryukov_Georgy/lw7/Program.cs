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
            Stopwatch sWatch = new Stopwatch();
            int[] kek = CArrayManager.fillArray("kek.txt");

            sWatch.Start();
            CArrayManipulator.sortingProcess(kek);
            sWatch.Stop();

            foreach (int k in kek)
            Console.WriteLine(k);
            Console.WriteLine(sWatch.ElapsedMilliseconds.ToString() + " ms");
        }
    }
}
