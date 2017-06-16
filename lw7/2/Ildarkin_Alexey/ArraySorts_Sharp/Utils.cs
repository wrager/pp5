using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Text;
using System.Threading.Tasks;

namespace ArraySorts_Sharp
{
    class Utils
    {
        public static List<int> ReadFileToVec(string filename)
        {
            List<int> numbers = File.ReadAllText(filename)
                .Split(new char[] { '\t', ' ', '\n' }, StringSplitOptions.RemoveEmptyEntries)
                .Where(x => x.All(char.IsDigit))
                .Select(int.Parse)
                .ToList();

            return numbers;
        }

        public static double NotifyExecutionTime(Action callback)
        {
            var watch = System.Diagnostics.Stopwatch.StartNew();
            callback();
            watch.Stop();
            return watch.ElapsedMilliseconds;
        }
    }
}
