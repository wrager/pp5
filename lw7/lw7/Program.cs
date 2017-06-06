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
                //setlocale(LC_ALL, "RUS");

                CheckParametrs(args.Length);

                //boost::timer::cpu_timer timer;

                ulong amountIteration = Convert.ToUInt64(args[0]);
                ulong processesNumber = Convert.ToUInt64(args[1]);

                //timer.start();
                Console.WriteLine("{0}", CTaskSolver.GetPi(amountIteration, processesNumber));

                //timer.stop();

                //double time = timer.elapsed().wall * pow(10.f, -9.f);
                //Console.WriteLine("time = {0}", time);

                Console.ReadKey();
                //system("pause");
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
