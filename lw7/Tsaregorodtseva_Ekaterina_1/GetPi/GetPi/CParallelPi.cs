using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Threading;
using System.Collections;

namespace GetPi
{
    class CParallelPi: IMonteCarloMethod
    {
        private double m_pi;
        public double Get() { return m_pi; }
        public void Calculate(int accuracy) {
            Stopwatch sWatch = new Stopwatch();
            sWatch.Start();

            int threadsNumb = Process.GetCurrentProcess().Threads.Count;
            
            int count = 0;
            Thread [] threadsList = new Thread[threadsNumb];
            ArrayList numbersList = new ArrayList(threadsNumb);
            for (int i = 0; i < threadsNumb; i++)
            {
                threadsList[i] = new System.Threading.Thread(delegate () { GetNumbRightPoints(accuracy/threadsNumb, ref numbersList); });
            }
            foreach (var th in threadsList)
            {
                th.Start();
            }
            foreach (var th in threadsList)
            {
                th.Join();
            }
            for (int i = 0; i < threadsNumb; i++)
            {
                count += (int)numbersList[i];
            }
            m_pi = (double)count / accuracy * 4;

            sWatch.Stop();
            TimeSpan tSpan;
            tSpan = sWatch.Elapsed;
            Console.WriteLine("Time with threads: " + tSpan.ToString());
        }
        private void GetNumbRightPoints(int iterations, ref ArrayList numbersList)
        {
            int count = 0;
            Random rand = new Random();
            double x, y;
            for (int i = 0; i < iterations; i++)
            {
                x = (double)rand.Next(-10000, 10000) / 10000;
                y = (double)rand.Next(-10000, 10000) / 10000;
                if ((x * x + y * y) <= 1) ++count;
            }
            numbersList.Add(count);
        }

    }
}
