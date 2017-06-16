using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LAB7
{
    class CMessage
    {
        private List<char> m_message;
        private CAlphabet m_alphabet;

        public CMessage(List<char> mMessage, CAlphabet mAlphabet)
        {
            m_message = mMessage;
            m_alphabet = mAlphabet;
        }

        public int GetSize()
        {
            return m_message.Count;
        }

        public List<char> GetCharMessage()
        {
            return m_message;
        }

        public void CondingForCaesar(Tuple<int, int> range, int key)
        {
            for (int i = range.Item1; i < range.Item2; i++)
            {
                int codeSymbol = m_alphabet.GetCodeForSymbol(m_message[i]);
                codeSymbol = (int) ((key + codeSymbol) % m_alphabet.GetSize());
                m_message[i] = m_alphabet.GetSymbolForCode(codeSymbol);
            }
        }

        public void CodingForGamma(Tuple<int, int> range, string gamma)
        {
            for (int i = range.Item1; i < range.Item2; i++)
            {
                int codeSymbol = m_alphabet.GetCodeForSymbol(m_message[i]);
                int codeGamma = m_alphabet.GetCodeForSymbol(gamma[i % gamma.Length]);
                codeSymbol = (int) ((codeGamma + codeSymbol) % m_alphabet.GetSize());
                m_message[i] = m_alphabet.GetSymbolForCode(codeSymbol);
            }
        }
    }
}
