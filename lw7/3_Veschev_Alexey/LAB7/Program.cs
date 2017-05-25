using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LAB7
{
    class Program
    {
        static void Main(string[] args)
        {
            CWorker worker = new CWorker();
            worker.EncipherCaesar("alphabet_eng.txt", "Harry_Potter_1_for_time.txt", 5);
            worker.EncipherGamma("alphabet_eng.txt", "Harry_Potter_1_for_time.txt", "gamma");
        }
    }
}
