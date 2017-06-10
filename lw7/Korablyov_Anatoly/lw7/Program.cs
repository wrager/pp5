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
            int[] sortedArrSeq = MergeSort.MergeSortSequence(nums);
            sWatch1.Stop();
            WriteToFile("sequence.txt", sortedArrSeq);

            sWatch2.Start();
            int[] sortedArrPar = lw7.MergeSort.MergeSortParallel(nums);
            sWatch2.Stop();
            WriteToFile("parallel.txt", sortedArrPar);

            Console.WriteLine("Sequence time measurement: " + sWatch1.ElapsedMilliseconds.ToString());
            Console.WriteLine("Parallel time measurement: " + sWatch2.ElapsedMilliseconds.ToString());

        }
    }
}
