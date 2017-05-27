using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;

namespace ArraySort
{
    class CalculatorAgregator
    {
        private ISortCalculator m_calc;
        private List<int> m_fileVec;

        public CalculatorAgregator(ref ISortCalculator calc, string filename)
        {
            m_calc = calc;
            m_fileVec = new List<int>();
            ReadListFromFile(filename);
        }

        public void Start()
        {
            SortArray(true);
            SortArray(false);
        }

        private void ReadListFromFile(string fileName)
        {
            using (TextReader reader = File.OpenText(fileName))
            {
                string[] text = reader.ReadToEnd().Split(' ');
                for(int i = 0; i < text.Length; i++)
                {
                    m_fileVec.Add(Convert.ToInt32(text[i]));
                }
            }
        }

        private void SortArray(bool parallel)
        {
            m_calc.Reset(new List<int>(m_fileVec));
            m_calc.Sort(parallel);
        }
    }
}
