using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace GetPi
{
    class CLinearPi: IMonteCarloMethod
    {
        private double m_pi;
        public double Get()
        { return m_pi; }
        public void Calculate(int accuracy) {
            Stopwatch sWatch = new Stopwatch();
            sWatch.Start();

            Random rand = new Random();

            int count = 0;
            double x, y;
            for (int i = 0; i < accuracy; i++)
            {
                x = (double)rand.Next(-10000,10000)/10000;
                y = (double)rand.Next(-10000, 10000) / 10000;
                if ((x * x + y * y) <= 1) ++count;
            }
            m_pi = (double)count / accuracy * 4;

            sWatch.Stop();
            TimeSpan tSpan;
            tSpan = sWatch.Elapsed;
            Console.WriteLine("Time without threads: " + tSpan.ToString());
        }
    }
}
