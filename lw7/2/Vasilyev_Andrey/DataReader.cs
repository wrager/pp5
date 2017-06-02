using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab7
{
    public static class DataReader
    {
        public static List<int> ReadFromFile(string filename)
        {
            var a = File.ReadAllText(filename);
            var numbers = File.ReadAllText(filename)
                .Split('\t', '\n', ' ')
                .Where(x => x.All(char.IsDigit))
                .Select(int.Parse)
                .ToList();

            return numbers;
        }
    }
}
