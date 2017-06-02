using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab7
{
    public class CSimpleShellSorter : CSorter
    {
        public CSimpleShellSorter(ArrayList data) : base(data)
        {
        }

        public override void Sort()
        {
            int n = m_data.Count;

            for (int h = n; h > 0; h /= 2)
            {
                int t;
                for (int i = h; i < n; i++)
                {
                    t = (int)m_data[i];
                    int j;
                    for (j = i; j >= h && t < (int)m_data[j - h]; j -= h)
                    {
                        m_data[j] = m_data[j - h];
                    }
                    m_data[j] = t;
                }
            }
        }

        public override string ToString()
        {
            return "SimpleShellSorter";
        }
    }
}
