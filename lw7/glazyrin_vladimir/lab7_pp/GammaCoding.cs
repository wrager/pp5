using System;
using System.Collections.Generic;
using System.Linq;
using System.Security;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace lab7_pp
{
    public class CGammaCoding
    {
        static StringBuilder[] stringArray;

        static void GammaTextCoding(object obj)
        {
            int countAlphabet = 0;
            Params param = (Params)obj;

            for (int i = param.start; i < param.finish; i++)
            {
                for (int j = 0; j < stringArray[i].Length - 2; j++)
                {               
                    int ascii_code = Convert.ToInt32(stringArray[i][j]);
                    ascii_code += Convert.ToInt32(Program.Alphabet[countAlphabet]);
                    ascii_code = ascii_code % 127;
                    countAlphabet = countAlphabet < Program.Alphabet.Length - 1 ? countAlphabet + 1 : 0;
                    stringArray[i][j] = Convert.ToChar(ascii_code);
                }
                countAlphabet = 0;
            }
        }

        public void WriteInFile(string fileName)
        {
            using (System.IO.StreamWriter outfile =
            new System.IO.StreamWriter(fileName))
            {
                for (int i = 0; i < stringArray.Length; i++)
                {
                    outfile.Write(stringArray[i].ToString());
                }
            }
        }

        public void SetStringArray(string[] str)
        {
            stringArray = new StringBuilder[str.Length];

            for (int i = 0; i < str.Length; i++)
            {
                StringBuilder sb = new StringBuilder();
                sb.AppendLine(str[i]);
                stringArray[i] = sb;
            }
        }

        public void CallConsistentMethod()
        {
            Params param = new Params();
            param.start = 0;
            param.finish = stringArray.Length;
            GammaTextCoding(param);
        }

        public void CallParallMethod(int countOfThreads)
        {
            Thread[] tasks = new Thread[countOfThreads];

            int sizeForEachThread = (stringArray.Length) / countOfThreads;

            for (int i = 0; i < countOfThreads; i++)
            {
                Params param2 = new Params();
                param2.start = i * sizeForEachThread;
                if (i + 1 < countOfThreads)
                {
                    param2.finish = i * sizeForEachThread + sizeForEachThread;
                }
                else
                {
                    param2.finish = i * sizeForEachThread + sizeForEachThread + (stringArray.Length) % countOfThreads;
                }
                tasks[i] = new Thread(GammaTextCoding);

                tasks[i].Start(param2);
            }

            for (int i = 0; i < countOfThreads; i++)
            {
                tasks[i].Join();
            }
        }
    }
}
