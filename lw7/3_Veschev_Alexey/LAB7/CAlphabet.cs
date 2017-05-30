using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LAB7
{
    class CAlphabet
    {
        private Dictionary<char, int> m_alphabet;

        public CAlphabet()
        {
            m_alphabet = new Dictionary<char, int>();
        }

        public void ReadFormFile(string fileName)
        {
            try
            {
                string startupPatch = Directory.GetParent(Directory.GetCurrentDirectory()).Parent.FullName;
                FileStream fstream = File.OpenRead(startupPatch + "/tests/" + fileName);
                byte[] array = new byte[fstream.Length];
                fstream.Read(array, 0, array.Length);
                char[] charArray =  System.Text.Encoding.Default.GetChars(array);

                m_alphabet.Clear();
                for (int i = 1; i <= charArray.Length; i++)
                {
                    m_alphabet.Add(charArray[i - 1], i);
                }
                
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                throw;
            }
           


        }

        public int GetCodeForSymbol(char symbol)
        {
            foreach (var varibale in m_alphabet)
            {
                if (varibale.Key == symbol)
                {
                    return varibale.Value;
                }
            }
            return -1;
        }

        public char GetSymbolForCode(int code)
        {
            foreach (var varibale in m_alphabet)
            {
                if (varibale.Value == code)
                {
                    return varibale.Key;
                }
            }
            return '-';
        }

        public long GetSize()
        {
           return m_alphabet.Count;
        }
    }
}
