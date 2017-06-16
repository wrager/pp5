using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lw7
{
    class MergeSort
    {

        public static int[] MergeTwoArray(int[] firstArr, int[] secondArr)
        {
            int[] resultArr = new int[firstArr.Length + secondArr.Length];
            int firstIndex = 0;
            int secIndex = 0;
            int resIndex = 0;
            while (resultArr.Length < firstArr.Length + secondArr.Length)
            {
                if (firstIndex >= firstArr.Length)
                {
                    for (int it = secIndex; it < secondArr.Length; it++)
                    {
                        resultArr[resIndex] = secondArr[it];
                        resIndex++;
                    }
                }
                else if (secIndex >= secondArr.Length)
                {
                    for (int it = firstIndex; it < firstArr.Length; it++)
                    {
                        resultArr[resIndex] = firstArr[it];
                        resIndex++;
                    }
                }
                else
                {
                    if (firstArr[firstIndex] <= secondArr[secIndex])
                    {
                        resultArr[resIndex] = firstArr[firstIndex];
                        resIndex++;
                        firstIndex++;
                    }
                    else
                    {
                        resultArr[resIndex] = secondArr[secIndex];
                        resIndex++;
                        secIndex++;
                    }
                }
            }
            return resultArr;
        }

        public static void ReplaceArrToTwoArr(int[] num, int[] firstArr, int[] secondArr)
        {
            int nElems = num.Length / 2;

            int fIndex = 0;
            int sIndex = 0;
            for (int i = 0; i < num.Length; i++)
            {
                if (nElems < 1)
                {
                    secondArr[sIndex] = num[i];
                    sIndex++;
                }
                else
                {
                    firstArr[fIndex] = num[i];
                    fIndex++;
                    nElems--;
                }
            }
        }

        public static int[] MergeSortSequence(int[] num)
        {
            if (num.Length > 1)
            {
                int nElems = num.Length / 2;
                int[] firstArr = new int[nElems];
                int[] secondArr = new int[num.Length - nElems];

                ReplaceArrToTwoArr(num, firstArr, secondArr);

                int[] fNewArr = MergeSortSequence(firstArr);
                int[] sNewArr = MergeSortSequence(secondArr);

                int[] resArr = MergeTwoArray(fNewArr, sNewArr);
                return resArr;
            }
            return num;
        }

        public static int[] MergeSortParallel(int[] num)
        {
            if (num.Length > 1)
            {
                int nElems = num.Length / 2;
                int[] firstArr = new int[nElems];
                int[] secondArr = new int[num.Length - nElems];

                ReplaceArrToTwoArr(num, firstArr, secondArr);

                int[] fNewArr = new int[firstArr.Length];
                int[] sNewArr = new int[secondArr.Length];
                Task thread1 = Task.Factory.StartNew(() => fNewArr = MergeSortSequence(firstArr));
                Task thread2 = Task.Factory.StartNew(() => sNewArr = MergeSortSequence(secondArr));
                Task.WaitAll(thread1, thread2);

                int[] resArr = MergeTwoArray(fNewArr, sNewArr);
                return resArr;
            }
            return num;
        }

    }
}
