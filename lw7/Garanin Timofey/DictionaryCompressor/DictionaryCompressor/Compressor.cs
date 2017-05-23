using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;

namespace DictionaryCompressor
{
    
    class Compressor
    {
        private string m_textFragment;
        private string m_incompleteWord;
        private string m_textFragmentAfterProcessing;
        private uint m_length;
        private int m_order;
        private RepositoryProcessedData m_repositoryProcessedData;
        private Dictionary<string, string> m_dictionary;
        private List<char> m_punctuation;
        private List<char> m_specials;
        private Mutex m_mutex;

        public Compressor(int order, RepositoryProcessedData repository, Mutex mutex)
        {
            m_mutex = mutex;
	        m_order = order;
            m_repositoryProcessedData = repository;
            m_punctuation = new List<char>(new char[]{ ',', '.', ';', ':', '?', '!', '-', '(', ')', '\'', '\"', ' ' });
	        m_specials = new List<char>(new char[] { '\n', '\t', '\r', '\f', '\b' });
	        m_dictionary = new Dictionary<string, string>();
            m_textFragmentAfterProcessing = "";

        }

        public void EditFragment()
        {
            string word = "";
            if (!String.IsNullOrEmpty(m_incompleteWord))
            {
                word = m_incompleteWord;
                m_incompleteWord.Remove(0);
            }
            bool ifPastWasPunctMark = false;
            for (int i = 0; i != m_textFragment.Length; ++i)
            {
                
                if (!IsPunctuaion(m_textFragment.ElementAt(i)) && !IsSpecials(m_textFragment.ElementAt(i)))
                {
                    var tt = m_textFragment.ElementAt(i).ToString();
                    word = word.Insert(word.Length, tt);
                    ifPastWasPunctMark = false;
                }
                else
                {
                    if (!ifPastWasPunctMark)
                    {
                        m_mutex.WaitOne() ;
                        string value = "";
                        var dict = m_repositoryProcessedData.GetDictionary();
                        if (!dict.TryGetValue(word, out value))
                        {
                            value = Convert.ToString(dict.Count);
                            dict.Add(word, value);
                        }
                        m_mutex.ReleaseMutex();
                        m_textFragmentAfterProcessing = m_textFragmentAfterProcessing.Insert(m_textFragmentAfterProcessing.Length, value);
				        if (!IsSpecials(m_textFragment.ElementAt(i)))
				        {
                            m_textFragmentAfterProcessing = m_textFragmentAfterProcessing.Insert(m_textFragmentAfterProcessing.Length, m_textFragment.ElementAt(i).ToString());
				        }
                        ifPastWasPunctMark = true;
                        word = word.Remove(0, word.Length);
                    }
			        else if (!IsSpecials(m_textFragment.ElementAt(i)))
			        {
                        m_textFragmentAfterProcessing = m_textFragmentAfterProcessing.Insert(m_textFragmentAfterProcessing.Length, m_textFragment.ElementAt(i).ToString());
			        }
		        }
		        if (IsSpecials(m_textFragment.ElementAt(i)))
		        {
                    m_textFragmentAfterProcessing = m_textFragmentAfterProcessing.Insert(m_textFragmentAfterProcessing.Length, m_textFragment.ElementAt(i).ToString());
                    word = word.Remove(0, word.Length);
                }
	        }
	        if (!String.IsNullOrEmpty(word))
	        {
		        m_incompleteWord = word;
	        }
        }

        public void SetTextFragment(string text)
        {
            m_textFragment = text;
        }

        public void SetLengthFragment(uint length)
        {
            m_length = length;
        }

        public int GetOrder()
        {
            return m_order;
        }

        public Dictionary<string, string> GetAllDictionary()
        {
	        return m_dictionary;
        }

        public string GetAllProcessingText()
        {
            return m_textFragmentAfterProcessing;
        }

        private bool IsPunctuaion(char c)
        {
            var index = m_punctuation.IndexOf(c);
            if (index == -1)
            {
                return false;
            }
            return true;
        }

        private bool IsSpecials(char c)
        {
            var index = m_specials.IndexOf(c);
            if (index == -1)
            {
                return false;
            }
            return true;
        }

    }
}
