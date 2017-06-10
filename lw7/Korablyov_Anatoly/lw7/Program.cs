using System;
using System.Collections.Generic;
using System.Linq;
using System.Diagnostics;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace lw7
{
    class Program
    {
        public static int[] ReadFile(string nameFile)
        {
            string file = File.ReadAllText(nameFile);

            int[] nums = file
            .Split(new char[] { ' ', ',' }, StringSplitOptions.RemoveEmptyEntries)
            .Select(n => int.Parse(n))
            .ToArray();
            return nums;
        }

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

        public static int[] MergeSort(int[] num)
        {
            if (num.Length > 1)
            {
                int nElems = num.Length / 2;
                int[] firstArr = new int[nElems];
                int[] secondArr = new int[num.Length - nElems];

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

                int[] fNewArr = MergeSort(firstArr);
                int[] sNewArr = MergeSort(secondArr);

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
                int[] fNewArr = new int[firstArr.Length];
                int[] sNewArr = new int[secondArr.Length];
                Task thread1 = Task.Factory.StartNew(() => fNewArr = MergeSort(firstArr));
                Task thread2 = Task.Factory.StartNew(() => sNewArr = MergeSort(secondArr));
                Task.WaitAll(thread1, thread2);

                int[] resArr = MergeTwoArray(fNewArr, sNewArr);
                return resArr;
            }
            return num;
        }

        public static void WriteToFile(string fileName, int[] nums)
        {
            FileStream aFile = new FileStream(fileName, FileMode.OpenOrCreate);
            StreamWriter sw = new StreamWriter(aFile);
            aFile.Seek(0, SeekOrigin.End);
            for (int i = 0; i < nums.Length; i++)
            {
                sw.Write(nums[i]);
                sw.Write(", ");
            }
            sw.Close();
        }

        static void Main(string[] args)
        {
            string path = args[0];
            int[] nums = ReadFile(path);

            Stopwatch sWatch1 = new Stopwatch();
            Stopwatch sWatch2 = new Stopwatch();

            sWatch1.Start();
            int[] sortedArrSeq = MergeSort(nums);
            sWatch1.Stop();
            WriteToFile("sequence.txt", sortedArrSeq);

            sWatch2.Start();
            int[] sortedArrPar = MergeSortParallel(nums);
            sWatch2.Stop();
            WriteToFile("parallel.txt", sortedArrPar);

            Console.WriteLine("Sequence time measurement: " + sWatch1.ElapsedMilliseconds.ToString());
            Console.WriteLine("Parallel time measurement: " + sWatch2.ElapsedMilliseconds.ToString());

        }
    }
}
