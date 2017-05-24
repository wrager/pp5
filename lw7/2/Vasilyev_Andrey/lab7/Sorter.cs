using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab7
{
    public abstract class CSorter
    {
        public enum Type
        {
            MERGE,
            SHELL
        };

        protected List<int> m_data;

        public List<int> Data
        {
            get
            {
                return m_data ?? new List<int>();
            }
            set
            {
                m_data = value;
            }
        }

        public CSorter(List<int> data)
        {
            m_data = data;
        }

        public abstract void Sort();
    }
}
