using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab7
{
    interface ISortCalculator
    {
        void Sort(bool isParallel);
        List<int> GetResult();
        void Reset(List<int> array);
    }
}
