using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LAB7
{
    class CLineCrypto : ICryptographer
    {

        private CMessage m_message;

        public CLineCrypto(List<char> message, CAlphabet alphabet)
        {
            m_message = new CMessage(message, alphabet);
        }
        public void EncipherCaesar(int key)
        {
            m_message.CondingForCaesar(new Tuple<int, int>(0, m_message.GetSize()), key);
        }

        public void EncipherGamma(string gamma)
        {
            if (gamma != "")
            {
                m_message.CodingForGamma(new Tuple<int, int>(0, m_message.GetSize()), gamma);
            }
        }

        public List<char> GetMessage()
        {
            return  m_message.GetCharMessage();
        }
    }
}
