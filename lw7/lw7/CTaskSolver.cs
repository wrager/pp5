using System;
using System.Collections.Generic;
using System.Threading;

namespace lw7
{
    internal class CTaskSolver
    {
        private ulong m_numberProcess;
        private ulong m_amountIterations;

        class ThreadResult
        {
            public ThreadResult()
            {

            }

            public ThreadResult(double res)
            {
                result = res;
            }
            public double result;
        };

        static public double GetPi(ulong amountIteration, ulong amountThreads)
        {
            double result = 0.0;

            List<Thread> threads = new List<Thread>();
            List<ThreadResult> threadResults = new List<ThreadResult>();

            for (ulong index = 0; index < amountThreads; ++index)
            {
                threadResults.Add(new ThreadResult());
                int intIndex = Convert.ToInt32(index);

                Thread thread = new Thread(
                    () =>
                    {
                        ComputePi(
                            index,
                            amountIteration / amountThreads,
                            amountIteration,
                            threadResults[intIndex]
                        );
                    }
                );
                thread.Start();
                thread.Join();
                threads.Add(thread);
            };

          

            for (int index = 0; index < Convert.ToInt32(amountThreads); ++index)
            {
                if (!threads[index].IsAlive)// was joinable
                {
                    result += threadResults[index].result;
                }
            }

            return result;
        }

        static private void ComputePi(
            ulong threadId,
            ulong amountIteration,
            ulong amountPoints,
            ThreadResult result//&
        )
        {
            //srand(UINT(time(NULL) + threadId));

            double resultTheThread = 0.0;

            // Получается(для 4 потоков) 4-верть пи из-за того берём четверть точек
            // и делим на кол-во итераций

            // один поток береёт четверть точек и вычисляет коэфициент для четверти
            resultTheThread = 4.0 * CalculateHits(amountIteration) / amountPoints;

            Console.WriteLine(GetMessageForThread(amountIteration, resultTheThread, threadId));

            result.result = resultTheThread;
        }

        static private double RandomNumber()
        {
            Random rand = new Random();
            return rand.NextDouble();
        }

        static private bool InCircle(double x, double y)
        {
            return (x * x + y * y) <= 1;
        }

        static private ulong CalculateHits(ulong numIter)
        {
            ulong numHits = 0;
            for (ulong index = 0; index < numIter; ++index)
            {
                if(InCircle(RandomNumber(), RandomNumber()))
                {
                    ++numHits;
                }
            }
            return numHits;
        }

        // Evenly distributes indexes on processors
        static private string GetMessageForThread(
            ulong amountIteration
            , double result
            , ulong indexThread
        )
        {
            string message = "Id thread "
                + indexThread.ToString() + "\n"
                + "Amount iteration = " + amountIteration.ToString() + "\n"
                + "Result = " + result.ToString() + "\n";

            return message;
        }

    }
}