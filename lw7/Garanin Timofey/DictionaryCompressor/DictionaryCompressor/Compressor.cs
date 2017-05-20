using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DictionaryCompressor
{
    
    class Compressor
    {
        private string m_textFragment;
        private string m_incompleteWord;
        private string m_textFragmentAfterProcessing;
        private uint m_length;
        private uint m_order;
        private RepositoryProcessedData m_repositoryProcessedData;
        private Dictionary<string, string> m_dictionary;
        private List<char> m_punctuation;
        private List<char> m_specials;

        Compressor(uint order, RepositoryProcessedData repository)
        {
	        m_order = order;
            m_repositoryProcessedData = repository;
            m_punctuation = new List<char>(new char[]{ ',', '.', ';', ':', '?', '!', '-', '(', ')', '\'', '\"', ' ' });
	        m_specials = new List<char>(new char[] { '\n', '\t', '\r', '\f', '\b' });
	        m_dictionary = new Dictionary<string, string>();
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
            for (int i = 0; i != m_length; ++i)
            {
                if (!IsPunctuaion(m_textFragment.ElementAt(i)) && !IsSpecials(m_textFragment.ElementAt(i)))
                {
                    word.Insert(word.Length - 1, m_textFragment.ElementAt(i).ToString());
                    ifPastWasPunctMark = false;
                }
                else
                {
                    if (!ifPastWasPunctMark)
                    {
                        //int number = 0;
                        //std::transform(word.begin(), word.end(), word.begin(), ::tolower);
                        word.ToLower();
                        //std::stringstream ss;

                        //m_mutex->lock () ;
                        string value = "";
                        var dict = m_repositoryProcessedData.GetDictionary();
                        if (!dict.TryGetValue(word, out value))
                        {

                            /*number = Convert.ToInt16(value);
                            ss << number;*/
                            value = Convert.ToString(dict.Count);
                            dict.Add(word, value);
                        }
                        /*else
                        {
                            number = static_cast<int>(dict->size());
                            ss << number;
                            dict->insert(std::pair < std::string, std::string > (word, std::string(ss.str())));
                        }*/
                        //m_mutex->unlock();

                        //std::string cv = std::string(ss.str());
                        m_textFragmentAfterProcessing.Insert(m_textFragmentAfterProcessing.Length, value);
				        //m_textFragmentAfterProcessing->insert(m_textFragmentAfterProcessing->end(), cv.begin(), cv.end());
				        if (!IsSpecials(m_textFragment.ElementAt(i)))
				        {
                            m_textFragmentAfterProcessing.Insert(m_textFragmentAfterProcessing.Length - 1, m_textFragment.ElementAt(i).ToString());
					        //m_textFragmentAfterProcessing->insert(m_textFragmentAfterProcessing->end(), m_pTextFragment[i]);
				        }
                        ifPastWasPunctMark = true;
				        //word.clear();
                        word.Remove(0);
                    }
			        else if (!IsSpecials(m_textFragment.ElementAt(i)))
			        {
				        m_textFragmentAfterProcessing.Insert(m_textFragmentAfterProcessing.Length - 1, m_textFragment.ElementAt(i).ToString());
			        }
		        }
		        if (IsSpecials(m_textFragment.ElementAt(i)))
		        {
			        m_textFragmentAfterProcessing.Insert(m_textFragmentAfterProcessing.Length - 1, m_textFragment.ElementAt(i).ToString());
                    //word.clear();
                    word.Remove(0);
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

        uint GetOrder()
        {
            return m_order;
        }

        Dictionary<string, string> GetAllDictionary()
        {
	        return m_dictionary;
        }

        string GetAllProcessingText()
        {
            return m_textFragmentAfterProcessing;
        }

        private bool IsPunctuaion(char c)
        {
            var index = m_punctuation.IndexOf(c);//std::find(m_punctuation.begin(), m_punctuation.end(), c);
            if (index == -1)
            {
                return false;
            }
            return true;
        }

        private bool IsSpecials(char c)
        {
            var index = m_specials.IndexOf(c);//std::find(m_specials.begin(), m_specials.end(), c);
            if (index == -1)
            {
                return false;
            }
            return true;
        }

    }
}
