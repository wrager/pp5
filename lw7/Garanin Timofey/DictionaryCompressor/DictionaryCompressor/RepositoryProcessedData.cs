using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DictionaryCompressor
{
    
    class RepositoryProcessedData
    {
        private Dictionary<string, string> m_dictionary;
        private string m_text;

        public void SetNewDictionaryFragment(Dictionary<string, string> dictionaryFragment)
        {
            m_dictionary = dictionaryFragment;
        }

        public void SetNewTextFragment(string text)
        {
            m_text = m_text.Insert(m_text.Length - 1, text);
        }

        public Dictionary<string, string> GetDictionary()
        {
	        return m_dictionary;
        }

        public string GetText()
        {
	        return m_text;
        }
    }
}
