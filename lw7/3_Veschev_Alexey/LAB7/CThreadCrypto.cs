using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace LAB7
{
    class CThreadCrypto : ICryptographer
    {
        List<Thread> m_threads;
        private CMessage m_message;
        private int m_countThreads;

        public CThreadCrypto(List<char> message, CAlphabet alphabet)
        {
            m_message = new CMessage(message, alphabet);
            m_countThreads = Process.GetCurrentProcess().Threads.Count;
        }

        public void EncipherCaesar(int key)

        {
            m_threads = new List<Thread>();
            for (int i = 0; i < m_countThreads - 1; i++)
            {
                m_threads.Add(new Thread(delegate() { Mediator(i, key); }));
                m_threads.Last().Start();
            }
            m_threads.ForEach(thread => thread.Join());
        }

   
        public void EncipherGamma(string gamma)
        {
            m_threads = new List<Thread>();
            for (int i = 0; i < m_countThreads - 1; i++)
            {
                m_threads.Add(new Thread(delegate () { Mediator(i, gamma); }));
                m_threads.Last().Start();
            }
            m_threads.ForEach(thread => thread.Join());
        }

        private void Mediator(int threadNumber, int key)
        {
            int size = m_message.GetSize();
            int minSize = size / m_countThreads * threadNumber;
            int maxSize = (threadNumber == (m_countThreads - 1) ? size : minSize + size / m_countThreads);
            m_message.CondingForCaesar(new Tuple<int, int>(minSize, maxSize), key);
        }

        private void Mediator(int threadNumber, string gamma)
        {
            int size = m_message.GetSize();
            int minSize = size / m_countThreads * threadNumber;
            int maxSize = (threadNumber == (m_countThreads - 1) ? size : minSize + size / m_countThreads);
            m_message.CodingForGamma(new Tuple<int, int>(minSize, maxSize), gamma);
        }

        public List<char> GetMessage()
        {
            return m_message.GetCharMessage();
        }
    }
}
