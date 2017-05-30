using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace app
{
    class Chronometer
    {
        public static double GetCalculatedTime(Action callback)
        {
            var watch = System.Diagnostics.Stopwatch.StartNew();
            callback();
            watch.Stop();
            return watch.ElapsedMilliseconds;
        }
    }
}
