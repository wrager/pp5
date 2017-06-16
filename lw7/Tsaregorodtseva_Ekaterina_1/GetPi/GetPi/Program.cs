using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GetPi
{
    class Program
    {
        static void Main(string[] args)
        {
            int chislo = Convert.ToInt32(args[0],10);

            CLinearPi linPi = new CLinearPi();
            linPi.Calculate(chislo);
            Console.WriteLine("Pi = " + linPi.Get() + "\n");

            CParallelPi paralPi = new CParallelPi();
            paralPi.Calculate(chislo);
            Console.WriteLine("Pi = " + paralPi.Get());
        }
    }
}
