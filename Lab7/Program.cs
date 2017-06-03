using System;
using System.Diagnostics;
using System.Linq;

class Program
{
    static double PiSequintal(double iterationsCount)
    {
        Random rand = new Random();
        int includedPoints = 0;
        for (int i = 0; i < iterationsCount; i++)
        {
            double x = rand.NextDouble() * 2 - 1;
            double y = rand.NextDouble() * 2 - 1;

            if (x * x + y * y <= 1)
            {
                includedPoints++;
            }
        }

        return 4.0 * (includedPoints / iterationsCount);
    }
        
    static void Main(string[] args)
    {
        double iterationsCount = 0;
        if (args.Length != 1)
        {
            Console.WriteLine("Wrong arguments! Enter the number of iterations!");
            return;
        }

        iterationsCount = double.Parse(args.First());

        Console.WriteLine("Sequential method");
        Stopwatch stopWatch = new Stopwatch();
        stopWatch.Start();
        Console.WriteLine("Result: {0:##.00000}", PiSequintal(iterationsCount));
        stopWatch.Stop();
        Console.WriteLine("Time: {0} \n", stopWatch.Elapsed);
    }
}