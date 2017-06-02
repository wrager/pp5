using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab7
{
    public class CSimpleMergeSorter : CSorter
    {
        protected ArrayList helper;

        public CSimpleMergeSorter(ArrayList data) : base(data)
        {
            helper = new ArrayList();
            for (int i = 0; i < data.Count; ++i)
            {
                helper.Add(0);
            }
        }

        public override void Sort()
        {
            helper = new ArrayList(m_data.Count);
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
            for (int ii = low; ii <= high; ++ii)
            {
                if(ii==m_data.Count)
                {
                    break;
                }
                helper[ii] = m_data[ii];
            }

            int i = low;
            int j = middle + 1;
            int k = low;

            while (i <= middle && j <= high)
            {
                if ((int)helper[i] <= (int)helper[j])
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