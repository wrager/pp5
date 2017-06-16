using System;
using System.Collections.Generic;
using System.Linq;
using System.Diagnostics;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.IO;

namespace PPLab7
{
    class Program
    {

        public static int[] fillArray(string path)
        {
            string file = File.ReadAllText(path);

            int[] nums = file
            .Split(new char[] { ' ', ',' }, StringSplitOptions.RemoveEmptyEntries)
            .Select(n => int.Parse(n))
            .ToArray();
            return nums;
        }

        public static void MergeSortParallel(int[] input, int low, int high)
        {

            if (low < high)
            {
                int middle = (low / 2) + (high / 2);
                Task thread1 = Task.Factory.StartNew(() => MergeSort(input, low, middle));
                Task thread2 = Task.Factory.StartNew(() => MergeSort(input, middle + 1, high));
                Task.WaitAll(thread1, thread2);
                Merge(input, low, middle, high);
            }
        }

        public static void MergeSort(int[] input, int low, int high)
        {
            if (low < high)
            {
                int middle = (low / 2) + (high / 2);
                MergeSort(input, low, middle);
                MergeSort(input, middle + 1, high);
                Merge(input, low, middle, high);
            }
        }


        private static void Merge(int[] input, int low, int middle, int high)
        {

            int left = low;
            int right = middle + 1;
            int[] tmp = new int[(high - low) + 1];
            int tmpIndex = 0;

            while ((left <= middle) && (right <= high))
            {
                if (input[left] < input[right])
                {
                    tmp[tmpIndex] = input[left];
                    left = left + 1;
                }
                else
                {
                    tmp[tmpIndex] = input[right];
                    right = right + 1;
                }
                tmpIndex = tmpIndex + 1;
            }

            if (left <= middle)
            {
                while (left <= middle)
                {
                    tmp[tmpIndex] = input[left];
                    left = left + 1;
                    tmpIndex = tmpIndex + 1;
                }
            }

            if (right <= high)
            {
                while (right <= high)
                {
                    tmp[tmpIndex] = input[right];
                    right = right + 1;
                    tmpIndex = tmpIndex + 1;
                }
            }

            for (int i = 0; i < tmp.Length; i++)
            {
                input[low + i] = tmp[i];
            }

        }



        static void Main(string[] args)
        {
            string path = args[0];
            int[] arrayForParallelMerge = fillArray(path);
            int[] arrayForMerge = fillArray(path);

            Stopwatch sWatch1 = new Stopwatch();
            Stopwatch sWatch2 = new Stopwatch();

            

            sWatch1.Start();
            MergeSort(arrayForMerge, 0, arrayForMerge.Length - 1); ;
            sWatch1.Stop();

            sWatch2.Start();
            MergeSortParallel(arrayForParallelMerge, 0, arrayForParallelMerge.Length - 1); ;
            sWatch2.Stop();
            
            Console.WriteLine("Merge pos: " + sWatch1.ElapsedMilliseconds.ToString());
            Console.WriteLine("Merge par: " + sWatch2.ElapsedMilliseconds.ToString());

        }

    }
}
