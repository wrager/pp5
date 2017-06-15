using System;
using System.Linq;
using System.IO;

using Matrix = System.Collections.Generic.List<System.Collections.Generic.List<int>>;
class ArrWriter
{
    public static Matrix fillArray(string path)
    {
        string file = File.ReadAllText(path);
        Matrix arr = new Matrix();
        int[] nums = file
        .Split(new char[] { ' ', ',' }, StringSplitOptions.RemoveEmptyEntries)
        .Select(n => int.Parse(n))
        .ToArray();

        foreach(int num in nums)
        {
            System.Collections.Generic.List<int> element = new System.Collections.Generic.List<int>();
            element.Add(num);
            arr.Add(element);
        }
        return arr;
    }

    public static void output(int[] array)
    {
        StreamWriter str = new StreamWriter("output.txt");
        for (int i = 0; i < array.Length; i++)
        {
            str.Write(array[i]);
            str.Write(" ");
        }
        str.Close();
    }
}
