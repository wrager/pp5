using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SortProject.Sorter
{
    public abstract class AbstractSorter<T> where T : IComparable
    {
        public abstract void Sort();

        public List<T> Lst
        {
            get
            {
                return _list ?? new List<T>();
            }
            set
            {
                _list = value;
            }
        } 

        protected List<T> _list;
    }
}
