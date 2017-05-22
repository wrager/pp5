using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab7
{
    static class Utils
    {
        public static List<int> ReadFile(string filename)
        {
            var numbers = File.ReadAllText(filename)
                .Split('\t', '\n')
                .Where(x => x.All(char.IsDigit))
                .Select(int.Parse)
                .ToList();

            return numbers;
        }

        public static void Merge(ref List<int> vec, int low, int mid, int high)
        {
            int left = low;
            int right = mid + 1;

            //std::vector<int> b(high - low + 1);
            List<int> b = new List<int>(new int[high - low + 1]);
            int cur = 0;

            while (left <= mid && right <= high)
            {
                if (vec[left] <= vec[right])
                {
                    b[cur++] = vec[left++];
                }
                else
                {
                    b[cur++] = vec[right++];
                }
            }

            while (left <= mid)
            {
                b[cur++] = vec[left++];
            }
            while (right <= high)
            {
                b[cur++] = vec[right++];
            }
            cur--;
            while (cur >= 0)
            {
                vec[low + cur] = b[cur];
                cur--;
            }
        }

        public static void InsertSort(ref List<int> vec, int i, int half)
        {
            int temp = 0;
            int j = 0;

            for (int f = half + i; f < vec.Count; f += half)
            {
                j = f;
                while (j > i && vec[j - half] > vec[j])
                {
                    temp = vec[j];
                    vec[j] = vec[j - half];
                    vec[j - half] = temp;
                    j -= half;
                }
            }
        }
    }
}
