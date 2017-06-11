using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Threading;
using System.Threading.Tasks;

using Matrix = System.Collections.Generic.List<System.Collections.Generic.List<int>>;

namespace lab7
{
    class Sorter
    {

        public void SetArray(Matrix array)
        {
            m_array = array;
        }

        public void SetThreadCount(int count)
        {
            m_threadCount = count;
        }

        public List<int> StartSort()
        {
            int blockSize = (int)Math.Ceiling((double)m_array.Count() / (double)m_threadCount);
            int targetPos = 0;
            Matrix resultVec = new Matrix();

            Task[] tasks = new Task[m_threadCount];
            int taskCount = 0;

            while (targetPos < m_array.Count())
            {
                Matrix tempVec;
                if (targetPos + blockSize < m_array.Count())
                {
                    tempVec = m_array.GetRange(targetPos, blockSize);
                }
                else
                {
                    tempVec = m_array.GetRange(targetPos, m_array.Count() - targetPos);
                }
                targetPos += blockSize;
                tasks[taskCount++] = Task.Factory.StartNew(() => SortVec(tempVec, resultVec));
            }
            Task.WaitAll(tasks);
            SortVec(resultVec, m_array);
            return m_array[m_array.Count() - 1];
        }

        public void SortVec(Matrix vecToSort, Matrix resultVec)
        {
            while (vecToSort.Count() > 1)
            {
                Matrix tempVec = new Matrix();
                int targetSize = (int)(Math.Ceiling((double)(vecToSort.Count()) / 2.0));
                while (tempVec.Count() < targetSize)
                {
                    if (vecToSort.Count() != 0)
                    {
                        if (vecToSort.Count() > 1)
                        {
                            int size = vecToSort.Count();
                            List<int> vec1 = vecToSort[size - 1];
                            vecToSort.RemoveRange(size - 1, 1);
                            size = vecToSort.Count();
                            List<int> vec2 = vecToSort[size - 1];
                            vecToSort.RemoveRange(size - 1, 1);
                            MergeVectors(vec1, vec2, tempVec);
                        }
                        else
                        {
                            tempVec.Add(vecToSort[vecToSort.Count() - 1]);
                        }
                    }
                }
                vecToSort = tempVec;
            }

            resultVec.Add(vecToSort[0]);
        }

        public void MergeVectors(List<int> vec1, List<int> vec2, Matrix mainVec)
        {

            List<int> resultVec = new List<int>();
            List<int> v1 = vec1;
            List<int> v2 = vec2;
            v1.Reverse();
            v2.Reverse();
            
            while(v1.Count() != 0 && v2.Count() != 0)
            {
                if (v1[v1.Count() - 1] > v2[v2.Count() - 1])
                {
                    resultVec.Add(v2[v2.Count() - 1]);
                    v2.RemoveAt(v2.Count() - 1);
                }
                else
                {
                    resultVec.Add(v1[v1.Count() - 1]);
                    v1.RemoveAt(v1.Count() - 1);
                }
            }
            resultVec.AddRange(v1);
            resultVec.AddRange(v2);
            mainVec.Add(resultVec);
        }

        private Matrix m_array;
        private int m_threadCount;
    }
}
