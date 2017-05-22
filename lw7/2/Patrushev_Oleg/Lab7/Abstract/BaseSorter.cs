using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab7.Abstract
{
    abstract class BaseSorter : ISorter
    {
        protected List<int> _vector;
        protected int _startVectorSize;

        public BaseSorter(List<int> vector)
        {
            _vector = vector;
            _startVectorSize = _vector.Count;
        }

        public List<int> GetData()
        {
            return _vector;
        }

        public void Sort()
        {
            SortIteration();
        }

        public abstract void SortIteration();
    }
}
