
using System;

namespace lw7.Calculators
{
    class MonteCarloPiCalculator : IMonteCarloPiCalculator
    {
        public double CalculatePi(double iterNum)
        {
            var utils = new Utils();
            int hitsAmount = 0;

            for (int i = 1; i < iterNum; i++)
            {
                if (utils.IsPointInCircle(utils.GetRandomDouble(), utils.GetRandomDouble()))
                {
                    hitsAmount++;
                }
            }
            double result = 4.0 * (hitsAmount / iterNum);

            return result;
        }
    }
}
