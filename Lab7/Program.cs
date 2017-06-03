using System;
using System.Diagnostics;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;

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

    static double PiParal(double iterationsCount)
    {
        int processCount = Environment.ProcessorCount;
        int iterationForThread = (int)Math.Ceiling(iterationsCount / processCount);
        int includedPoints = 0;
        
        ParallelOptions options = new ParallelOptions();
        options.MaxDegreeOfParallelism = processCount;
        Parallel.For(0, processCount, options, i =>
        {
        Random rand = new Random();
            int threadIncludedPoints = 0;
            for (int j = 0; j < iterationForThread; j++)
            {
                double x = rand.NextDouble() * 2 - 1;
                double y = rand.NextDouble() * 2 - 1;

                if (x * x + y * y <= 1)
                {
                    threadIncludedPoints++;
                }
            }            
        Interlocked.Add(ref includedPoints, threadIncludedPoints);
        });

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

        Console.WriteLine("Parallel method");
        Stopwatch stopWatch = new Stopwatch();
        stopWatch.Start();
        Console.WriteLine("Result: {0:##.00000}", PiParal(iterationsCount));
        stopWatch.Stop();
        Console.WriteLine("Time: {0} \n", stopWatch.Elapsed);

        Console.WriteLine("Sequential method");
        stopWatch.Start();
        Console.WriteLine("Result: {0:##.00000}", PiSequintal(iterationsCount));
        stopWatch.Stop();
        Console.WriteLine("Time: {0} \n", stopWatch.Elapsed);
    }
}