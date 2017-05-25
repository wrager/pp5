using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace LAB7
{
    class CWorker
    {
        public List<char> ReadFormFile(string fileName)
        {
            List<char> message = new List<char>();
            StreamReader fReader = null;
            try
            {
                string startupPatch = Directory.GetParent(Directory.GetCurrentDirectory()).Parent.FullName;
                fReader = new StreamReader(startupPatch + "/tests/" + fileName);
                message = new List<char>(fReader.ReadToEnd());
                return message;
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                throw;
            }
            finally
            {
                fReader.Close();
            }

        }

        public void WriteMessageToFile(List<char> message, string fileStr)
        {
            StreamWriter fWriter = null;
            try
            {
                string startupPatch = Directory.GetParent(Directory.GetCurrentDirectory()).Parent?.FullName;
                fWriter = new StreamWriter(startupPatch + "/tests/" + fileStr);
                fWriter.Write(message.ToArray());
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                throw;
            }
            finally
            {
                fWriter?.Close();
            }
        }

        public void EncipherCaesar(string alphabetFile, string fileStr, int key)
        {
            CAlphabet alphabet = new CAlphabet();
            alphabet.ReadFormFile(alphabetFile);
            List<char> messageForLine = ReadFormFile(fileStr);
            List<char> messageForThread = messageForLine;
            //Line
            CLineCrypto lineCrypto = new CLineCrypto(messageForLine, alphabet);
            Console.WriteLine("Start Encipher Caesar");
            Stopwatch timer = Stopwatch.StartNew();
            lineCrypto.EncipherCaesar(key);
            long elapsedTimeForLine = timer.ElapsedMilliseconds;
            Console.Write(elapsedTimeForLine.ToString());
            Console.WriteLine(" ms. for line");
            WriteMessageToFile(messageForLine, "out_line_Caesar.txt");
            //Thread
        }
    }
}
