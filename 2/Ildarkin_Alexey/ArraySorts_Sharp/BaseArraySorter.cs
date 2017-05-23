using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ArraySorts_Sharp
{
    abstract class BaseArraySorter: IArraySorter
    {
        public abstract void Sort();

        public List<int> GetResult()
        {
            return _result;
        }

        protected BaseArraySorter(List<int> src, bool isParallelMode)
        {
            _result = src;
            _isParallelMode = isParallelMode;
        }

        protected List<int> _result;
        protected bool _isParallelMode;
    }
}
