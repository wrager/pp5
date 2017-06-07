using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lw7
{
    class Program
    {
        private const string MESSAGE_INCORRECT_AMOUNT_ARGUMENTS = "Incorrect amount arguments! Must will be ";
        private const int AMOUNT_ARGUMENTS = 2;


        static public void CheckParametrs(int argc)
        {
            if (argc != AMOUNT_ARGUMENTS)
            {
                throw new ArgumentException(MESSAGE_INCORRECT_AMOUNT_ARGUMENTS + AMOUNT_ARGUMENTS.ToString());
            }
        }

        static int Main(string[] args)
        {
            try
            {
                CheckParametrs(args.Length);

                ulong amountIteration = Convert.ToUInt64(args[0]);
                ulong processesNumber = Convert.ToUInt64(args[1]);

                CTaskSolver solver = new CTaskSolver();
                var watch = System.Diagnostics.Stopwatch.StartNew();
                Console.WriteLine("{0}", solver.GetPi(amountIteration, processesNumber));
                watch.Stop();

                Console.WriteLine("time = {0}", Convert.ToDouble(watch.ElapsedMilliseconds) / 1000);
                Console.ReadKey();
            }
            catch (Exception except)
            {
                Console.WriteLine(except.ToString());
                Console.ReadKey();
                return 1;
            }

            return 0;
        }
    }

}
