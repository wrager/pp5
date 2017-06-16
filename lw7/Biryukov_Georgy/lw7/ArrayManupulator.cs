using System;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;

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

    public static int[] sortingProcessParallel(int[] array)
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

    private static void MergeSort(int[] input)
    {
        MergeSort(input, 0, input.Length - 1);
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
}