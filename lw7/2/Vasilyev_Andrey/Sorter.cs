using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab7
{
    public abstract class Sorter
    {
        public enum Type
        {
            MERGE,
            SHELL
        };

        public List<int> Data { get; set; }

        public Sorter(List<int> data)
        {
            Data = data;
        }

        public abstract void Sort();
        public abstract override string ToString();
    }
}
