using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

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