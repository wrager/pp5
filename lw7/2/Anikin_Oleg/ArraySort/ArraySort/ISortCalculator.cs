using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArraySort
{
    public interface ISortCalculator
    {
        void Sort(bool isParallel);
        List<int> GetResult();
        void Reset(List<int> array);
    }
}
