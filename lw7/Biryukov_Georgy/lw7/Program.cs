using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace lw7
{
    class CArrayManager
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
    }

    class CArrayManipulator
    {
        public static int[] sortingProcess(int[] array)
        {
            int gap = array.Length / 2;
            while (gap > 0)
            {
                insertionSorting(array, gap);
                if (gap == 2) 
                {
                    gap = 1;
                }
                else
                {
                    gap = (int)(gap / 2.2);
                }
            }
            return array;
        }

        static void insertionSorting(int[] array, int gap)
        {
            for (int i = 0; i < array.Length - gap; i++)
            {
                int j = i + gap;
                int tmp = array[j];
                while (j >= gap && tmp > array[j - gap])
                {
                    array[j] = array[j - gap];
                    j -= gap;
                }
                array[j] = tmp;
            }
        }
    }

    class CMainProgram
    {
        static void Main(string[] args)
        {
            int[] kek = CArrayManager.fillArray(args[0]);
            CArrayManipulator.sortingProcess(kek);

            foreach (int k in kek)
                 Console.WriteLine(k);
        }
    }
}
