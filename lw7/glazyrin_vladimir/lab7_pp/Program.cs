using System;
using System.Collections.Generic;
using System.Linq;
using System.Security;
using System.Text;
using System.Threading;
using System.Threading.Tasks;


namespace lab7_pp_gamma
{
    class Program
    {
        static string[] m_text;
        static List<string> new_text;
        static string alphabet;
        static Encoding cyrillic = Encoding.UTF8;


        static SecureString GetPassword()
        {
            var pwd = new SecureString();
            while (true)
            {
                ConsoleKeyInfo i = Console.ReadKey(true);
                if (i.Key == ConsoleKey.Enter)
                {
                    break;
                }
                else if (i.Key == ConsoleKey.Backspace)
                {
                    if (pwd.Length > 0)
                    {
                        pwd.RemoveAt(pwd.Length - 1);
                        Console.Write("\b \b");
                    }
                }
                else
                {
                    pwd.AppendChar(i.KeyChar);
                    Console.Write("*");
                }
            }
            Console.WriteLine();
            return pwd;
        }

        static List<string> GammaTextCoding(int start, int finish)
        {
            int countAlphabet = 0;
            for (int i = start; i < finish; i++)
            {
                char[] line = new_text[i].ToCharArray();
                for (int j = start; j < line.Length; j++)
                {
                    int ascii_code = Convert.ToInt32(line[j]);
                    ascii_code += Convert.ToInt32(alphabet[countAlphabet]);
                    ascii_code = ascii_code % 127;
                    countAlphabet = countAlphabet < alphabet.Length - 1 ? countAlphabet + 1 : 0;
                    line[j] = Convert.ToChar(ascii_code);
                }
                new_text.RemoveAt(i);
                new_text.Insert(i, new string(line));
            }
            return new_text;
        }

        static string LoadAlphabet()
        {
            Console.WriteLine("enter alphabet : ");

            string numStr = new System.Net.NetworkCredential(string.Empty, GetPassword()).Password;

            return numStr;
        }

        public string ReplaceCharInString(string source, int index, char newSymb)
        {
            char[] chars = source.ToCharArray();
            chars[index] = newSymb;
            return new string(chars);
        }

        public static void Fill(List<string> list)
        {
            for (var i = 0; i < list.Capacity; i++)
            {
                list.Add("");
            }
        } 

        static void Main(string[] args)
        {
            alphabet = LoadAlphabet();

            m_text = System.IO.File.ReadAllLines("input.txt");

            new_text = new List<string>(m_text.Length);
            System.Diagnostics.Stopwatch startTime = new System.Diagnostics.Stopwatch();
            startTime.Start();
            
            for (int i = 0; i < m_text.Length; i++)
            {
                new_text.Add(m_text[i]);
            }

            GammaTextCoding(0, m_text.Length);

            startTime.Stop();

            Console.WriteLine("consistent method take " + (startTime.ElapsedMilliseconds / 1000.0).ToString());
           
            System.IO.File.WriteAllLines("output.txt", new_text);

            Console.Read();
        }
    }
}
