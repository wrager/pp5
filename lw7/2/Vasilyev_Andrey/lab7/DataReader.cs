using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab7
{
    public class DataReader
    {
        public static List<int> ReadFromFile(string inputFileName = "input.txt")
        {
            List<int> result = new List<int>();

            string[] data = File.ReadAllLines(inputFileName);
            for (int x = 0; x < data.Length; x++)
            {
                string[] temp = data[x].Split(' ');
                //assuming the first result is only used for being an index
                for (int y = 1; y < temp.Length; y++)
                {
                    if (temp[y].ToString().Length > 0)
                    {
                        result.Add(Convert.ToInt32(temp[y]));
                    }
                }
            }
            return result;
        }
    }
}