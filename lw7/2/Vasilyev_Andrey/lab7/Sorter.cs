using System;
using System.Collections;
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

        protected ArrayList m_data;

        public ArrayList Data
        {
            get
            {
                return m_data ?? new ArrayList();
            }
            set
            {
                m_data = value;
            }
        }

        public CSorter(ArrayList data)
        {
            m_data = data;
        }

        public abstract void Sort();
    }
}
