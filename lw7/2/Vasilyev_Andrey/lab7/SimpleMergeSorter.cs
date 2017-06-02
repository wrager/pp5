using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab7
{
    public class SimpleMergeSorter: Sorter
    {
        protected List<int> helper;

        public SimpleMergeSorter(List<int> data)
            : base(data)
        {
            helper = new List<int>(new int[Data.Count + 1]);
        }

        public override void Sort()
        {
            MergeSort(0, Data.Count - 1);
        }

        public override string ToString()
        {
            return "Simple mergeSorter";
        }

        protected void MergeSort(int low, int high)
        {
            if (low < high)
            {
                int middle = low + (high - low) / 2;
                MergeSort(low, middle);
                MergeSort(middle + 1, high);
                Merge(low, middle, high);
            }
        }

        protected void Merge(int low, int middle, int high)
        {
            for (int m = low; m <= high; m++)
            {
                helper[m] = Data[m];
            }

            int i = low;
            int j = middle + 1;
            int k = low;

            while (i <= middle && j <= high)
            {
                if (helper[i] <= helper[j])
                {
                    Data[k] = helper[i];
                    i++;
                }
                else
                {
                    Data[k] = helper[j];
                    j++;
                }
                k++;
            }

            while (i <= middle)
            {
                Data[k] = helper[i];
                k++;
                i++;
            }
        }
    }
}
