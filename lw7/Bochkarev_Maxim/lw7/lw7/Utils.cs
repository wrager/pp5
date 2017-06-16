using System;

namespace lw7
{
    internal class Utils
    {
        private readonly Random _rand = new Random();
        internal double GetRandomDouble()
        {
            return _rand.NextDouble() * 2 - 1;
        }

        internal bool IsPointInCircle(double x, double y)
        {
            return (x * x + y * y) <= 1;
        }
    }
}