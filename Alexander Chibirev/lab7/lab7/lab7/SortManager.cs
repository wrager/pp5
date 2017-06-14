using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace lab7
{
    class SortManager
    {
        private ISortCalculator m_calc;
        private List<int> m_fileVec;

        public SortManager(ref ISortCalculator calc, string filename)
        {
            m_calc = calc;
            m_fileVec = new List<int>();
            GetDataFromFile(filename);
        }

        public void Start()
        {
            OutputWorkTime(() => SortArray(true));
            OutputWorkTime(() => SortArray(false));
        }

        private void OutputWorkTime(Action callback)
        {
            var watch = System.Diagnostics.Stopwatch.StartNew();
            callback();
            watch.Stop();
            Console.WriteLine(watch.ElapsedMilliseconds);
        }

        private void GetDataFromFile(string fileName)
        {
            using (TextReader reader = File.OpenText(fileName))
            {
                string[] text = reader.ReadToEnd().Split(' ');
                for (int i = 0; i < text.Length; i++)
                {
                    m_fileVec.Add(Convert.ToInt32(text[i]));
                }
                reader.Close();
            }
        }

        private void SortArray(bool parallel)
        {
            m_calc.Reset(new List<int>(m_fileVec));
            m_calc.Sort(parallel);
        }
    }
}
