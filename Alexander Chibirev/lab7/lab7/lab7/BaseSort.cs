using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab7
{
    abstract class BaseSort : ISortCalculator
    {

        protected BaseSort()
        {
            List<int> vec = new List<int>();
            m_array = vec;
        }

        public List<int> GetResult()
        {
            return m_array;
        }

        public void Reset(List<int> array)
        {
            m_array = array;
        }

        public void Sort(bool isParallel)
        {
            m_isParallelEnabled = isParallel;
            SortArray();
        }

        protected abstract void SortArray();

        protected List<int> m_array;
        protected bool m_isParallelEnabled = false;
    }
}
