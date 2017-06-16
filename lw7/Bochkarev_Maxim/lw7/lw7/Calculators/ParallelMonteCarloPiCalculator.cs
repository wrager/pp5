using System;
using System.Threading;
using System.Threading.Tasks;

namespace lw7.Calculators
{
    public class ParallelMonteCarloPiCalculator : IMonteCarloPiCalculator
    {
        public double CalculatePi(double iterNum)
        {
            int procNum = Environment.ProcessorCount;
            int iterOnThread = (int)Math.Ceiling(iterNum / procNum);
            int hitsAmount = 0;

            Parallel.For(0, procNum, new ParallelOptions {MaxDegreeOfParallelism = procNum}, i =>
            {
                Utils utils = new Utils();
                int threadHitsAmount = 0;

                for (int j = 0; j < iterOnThread; j++)
                {
                    if (utils.IsPointInCircle(utils.GetRandomDouble(), utils.GetRandomDouble()))
                    {
                        threadHitsAmount++;
                    }
                }
                Interlocked.Add(ref hitsAmount, threadHitsAmount);
            });

            double result = 4.0 * (hitsAmount / iterNum);
            return result;
        }
    }
}