using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace lw7
{
    class FileReader
    {
        public static List<int> fillArray(string path)
        {
            string file = File.ReadAllText(path);
            List<int> arr = new List<int>();
            int[] nums = file
            .Split(new char[] { ' ', ',' }, StringSplitOptions.RemoveEmptyEntries)
            .Select(n => int.Parse(n))
            .ToArray();
            foreach (int num in nums)
            {
                arr.Add(num);
            }
            return arr;
        }
    }
}
