using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab7
{
    public class CSimpleMergeSorter : CSorter
    {
        protected List<int> helper;

        public CSimpleMergeSorter(List<int> data) : base(data)
        {

        }

        public override void Sort()
        {
            helper = new List<int>(m_data.Count);
            for (int i = 0; i < m_data.Count; ++i)
            {
                helper.Add(0);
            }
            
            MergeSort(0, m_data.Count - 1);
        }

        public override string ToString()
        {
            return "SimpleMergeSorter";
        }

        public void MergeSort(int low, int high)
        {
            if (low < high)
            {
                int middle = low + (high - low) / 2;
                MergeSort(low, middle);
                MergeSort(middle + 1, high);
                Merge(low, middle, high);
            }
        }

        public void Merge(int low, int middle, int high)
        {
            for (int ii = low; ii <= high; ii++)
            {
                helper[ii] = m_data[ii];
            }

            int i = low;
            int j = middle + 1;
            int k = low;

            while (i <= middle && j <= high)
            {
                if (helper[i] <= helper[j])
                {
                    m_data[k] = helper[i];
                    i++;
                }
                else
                {
                    m_data[k] = helper[j];
                    j++;
                }
                k++;
            }

            while (i <= middle)
            {
                m_data[k] = helper[i];
                k++;
                i++;
            }
        }
    }
}