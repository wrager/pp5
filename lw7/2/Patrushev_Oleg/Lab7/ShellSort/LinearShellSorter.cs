using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab7.ShellSort
{
    class LinearShellSorter : BaseShellSorter
    {
        public LinearShellSorter(List<int> vector)
            : base(vector)
        {

        }

        protected override void ShellSort()
        {
            for (int h = _vector.Count / 2; h > 0; h = h / 2)
            {
                for (int i = 0; i < h; i++)
                {
                    Utils.InsertSort(ref _vector, i, h);
                }
            }
        }
    }
}
