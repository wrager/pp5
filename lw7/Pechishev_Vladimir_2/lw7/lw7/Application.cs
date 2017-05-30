using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.IO;


namespace app
{

    class CApplication
    {
        private List<int> m_array;
        private ArraySort.CMergeSort m_sorted = new ArraySort.CMergeSort();

        public CApplication(string inputPath)
        {
            m_array = ReadFileToVec(inputPath);
        }

        public void SortArray()
        {
            List<int> newList = GetCopyArray(m_array);
            List<int> newList2 = GetCopyArray(m_array);
            double timeForParallelVersionAglorithm = Chronometer.GetCalculatedTime(() => {
               m_sorted.Sort(newList, true);
            });
           
            double timeForSingleVersionAglorithm = Chronometer.GetCalculatedTime(() => {
                m_sorted.Sort(newList2, false);
            });

            Console.WriteLine("Time parallel algorithm: " + timeForParallelVersionAglorithm + "ms");
            Console.WriteLine("Time single algorithm: " + timeForSingleVersionAglorithm + "ms");
        }

        public static List<int> ReadFileToVec(string filename)
        {
            List<int> numbers = File.ReadAllText(filename)
                .Split(new char[] { '\t', ' ', '\n' }, StringSplitOptions.RemoveEmptyEntries)
                .Where(x => x.All(char.IsDigit))
                .Select(int.Parse)
                .ToList();

            return numbers;
        }

        List<int> GetCopyArray(List<int> array)
        {
            List<int> newList = new List<int>();
            for (int i = 0; i < array.Count; i++)
            {
                newList.Add(array[i]);
            }
            return newList;
        }
    }
}
