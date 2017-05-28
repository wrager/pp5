using System;
using System.Collections.Generic;
using System.Linq;
using System.Security;
using System.Text;
using System.Threading;
using System.Threading.Tasks;


namespace lab7_pp
{
    class Program
    {
        static string[] m_text;
        static string alphabet;

        public static string Alphabet
        {
            get
            {
                return alphabet;
            }
        }

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

        static string LoadAlphabet()
        {
            Console.WriteLine("enter alphabet : ");

            string numStr = new System.Net.NetworkCredential(string.Empty, GetPassword()).Password;

            return numStr;
        }

        static void Main(string[] args)
        {
            alphabet = LoadAlphabet();

            m_text = System.IO.File.ReadAllLines(args[0]);

            CGammaCoding code = new CGammaCoding();
            code.SetStringArray(m_text);
            
            System.Diagnostics.Stopwatch startTime1 = new System.Diagnostics.Stopwatch();
            startTime1.Start();
            code.CallConsistentMethod();
            startTime1.Stop();
            Console.WriteLine("consistent method take " + (startTime1.ElapsedMilliseconds / 1000.0).ToString());
            code.WriteInFile("consistent.txt");

            code.SetStringArray(m_text);
            int countOfThreads = Convert.ToInt32(args[1]);
            System.Diagnostics.Stopwatch startTime2 = new System.Diagnostics.Stopwatch();
            startTime2.Start();
            code.CallParallMethod(countOfThreads);
            startTime2.Stop();
            Console.WriteLine("parall method take " + (startTime2.ElapsedMilliseconds / 1000.0).ToString());
            code.WriteInFile("parall.txt");



        }
    }
    public class Params
    {
        public int start;
        public int finish;
    }

}

