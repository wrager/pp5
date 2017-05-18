using System;
using System.Diagnostics;
using System.Linq;
using lw7.Calculators;

namespace lw7
{
    class Program
    {
        static void Main(string[] args)
        {
            double iterNum = ReadCommandLineParameters(args);
            if (iterNum == -1)
            {
                Console.ReadLine();
                return; 
            }

            Console.WriteLine("Program started SERIAL Monte Carlo Pi Calculation with {0} iterations", iterNum);
            RunMonteCarloPiCalculation(new MonteCarloPiCalculator(), iterNum);

            Console.WriteLine("Program started PARALLEL Monte Carlo Pi Calculation with {0} iterations", iterNum);
            RunMonteCarloPiCalculation(new ParallelMonteCarloPiCalculator(), iterNum);

            Console.ReadLine();
        }

        static void RunMonteCarloPiCalculation(IMonteCarloPiCalculator calculator, double iterNum)
        {
            Stopwatch stopwatch = Stopwatch.StartNew();
            stopwatch.Restart();
            Console.WriteLine("Result: {0:##.00000}", calculator.CalculatePi(iterNum));
            stopwatch.Stop();
            Console.WriteLine("Execution Time: {0} \n", stopwatch.Elapsed);
        }

        static double ReadCommandLineParameters(string[] args)
        {
            double result = 0;
            if (args.Length != 1)
            {
                Console.WriteLine("Incorrect amount of parameters. Use /? for help. ");
                return -1;
            }
            if (args.First() == "/?")
            {
                Console.WriteLine("Program takes 1 argument: \n - iteration number \n\n Example: lw7.exe 100000");
                return -1;
            }

            try
            {
                result = double.Parse(args.First());
            }
            catch (Exception e)
            {
                Console.WriteLine("Command line parameters read error. Run app with /? to help.\\n");
                return -1;
            }

            if (result <= 0)
            {
                Console.WriteLine("Zero or negative iteration amount. Program stoped.");
                return -1;
            }

            return result;
        }
    }
}
