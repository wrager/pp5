using System;
using System.Threading;
using System.Threading.Tasks;

class CArrayManipulator
{
    public static int[] sortingProcess(int[] array)
    {
        int gap = array.Length / 2;
        while (gap > 0)
        {
            Thread thread = new Thread(delegate ()
            {
                insertionSorting(array, gap);
            });
            thread.Start();

            if (gap == 2)
            {
                gap = 1;
            }
            else
            {
                gap = (int)(gap / 2.2);
            }
            Thread.Sleep(0);
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