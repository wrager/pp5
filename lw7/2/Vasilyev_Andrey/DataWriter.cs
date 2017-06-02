using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab7
{
    public class DataWriter
    {

        public static void WriteToFile(List<int> data, string outputFileName = "output.txt")
        {
            // Write the string to a file.
            System.IO.StreamWriter file = new System.IO.StreamWriter(outputFileName);
            for (int i = 0; i < data.Count; ++i)
            {
                file.Write(data[i]);
                file.Write(" ");
            }
            file.Close();
        }
    }
}
