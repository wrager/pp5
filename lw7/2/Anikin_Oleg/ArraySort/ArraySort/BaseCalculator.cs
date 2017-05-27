using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace ArraySort
{
    abstract class BaseCalculator : ISortCalculator
    {
        public void Sort(bool isParallel)
        {
            m_isParallelEnabled = isParallel;
            SortBehavior();
        }

        public List<int> GetResult()
        {
            return m_array;
        }

        public void Reset(List<int> array)
        {
            m_array = array;
        }

        protected BaseCalculator(List<int> vec)
        {
            m_array = vec;
        }

        protected abstract void SortBehavior();

        protected List<int> m_array;
        protected bool m_isParallelEnabled = false;
    }
}
