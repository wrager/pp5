using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab7
{
    public class SimpleShellSorter: Sorter
    {
        public SimpleShellSorter(List<int> data)
            : base(data)
        {

        }

        public override void Sort()
        {
            int n = Data.Count;

            for (int h = n; h > 0;  h /= 2)
            {
                int t;
                for (int i = h; i < n; i++)
                {
                    t = Data[i];
                    int j;
                    for (j = i; j >= h && t < Data[j - h]; j -= h)
                    {
                        Data[j] = Data[j - h];
                    }
                    Data[j] = t;
                }
            }
        }

        public override string ToString()
        {
            return "Simple shellSorter";
        }
    }
}
