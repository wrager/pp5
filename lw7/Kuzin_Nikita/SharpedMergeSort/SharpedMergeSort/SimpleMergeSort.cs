using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.IO;

class CSimpleMergeSort
{
    private string m_input;
    private string m_output;
    private List<Thread> m_simpleThreadPool;

    public CSimpleMergeSort(string inputFilename, string outputFilename)
    {
        m_input = inputFilename;
        m_output = outputFilename;
        m_simpleThreadPool = new List<Thread>();
    }

    public void Execute()
    {
        WriteResult(SimpleMergeSort(ReadStart()));
    }

    private static List<int> MergeVectors(List<int> vec1, List<int> vec2)
    {
        List<int> temp1 = new List<int>(vec1);
        List<int> temp2 = new List<int>(vec2);

        List<int> resultVec = new List<int>();
        temp1.Reverse();
        temp2.Reverse();
        while (temp1.Any() && temp2.Any())
        {
            if (temp1.Last() > temp2.Last())
            {
                resultVec.Add(temp2.Last());
                temp2.RemoveAt(temp2.Count() - 1);
            }
            else
            {
                resultVec.Add(temp1.Last());
                temp1.RemoveAt(temp1.Count() - 1);
            }
        }
        while (temp1.Any())
        {
            resultVec.Add(temp1.Last());
            temp1.RemoveAt(temp1.Count() - 1);
        }
        while (temp2.Any())
        {
            resultVec.Add(temp2.Last());
            temp2.RemoveAt(temp2.Count() - 1);
        }
        return resultVec;

    }

    private List<int> ReadStart()
    {
        FileStream inputStream = new FileStream(@m_input, FileMode.OpenOrCreate, FileAccess.Read);
        StreamReader reader = new StreamReader(inputStream);
        List<int> temp = new List<int>();
        while (!reader.EndOfStream)
	    {
            temp.Add(Int32.Parse(reader.ReadLine()));
        }
        reader.Close();
        return temp;
    }

    private void WriteResult(List<int> result)
    {
        FileStream outputStream = new FileStream(@m_output, FileMode.OpenOrCreate, FileAccess.Write);
        StreamWriter writer = new StreamWriter(outputStream);
        foreach (int value in result)
        {
            writer.WriteLine(value);
        }
        writer.Close();
    }

    private List<int> SimpleMergeSort(List<int> source)
    {
        List<List<int>> splitedStart = new List<List<int>>();

        for (int i = 0; i < source.Count(); i++)
        {
            List<int> subList = new List<int>();
            subList.Add(source[i]);
            splitedStart.Add(subList);
        }

        Mutex mutex = new Mutex();
	    while (splitedStart.Count() > 1)
	    {
		    List<List<int>> temp = new List<List<int>>();
		    for (int i = 0; i <= splitedStart.Count() - 2; i += 2)
		    {
                ParameterizedThreadStart del = (pos) =>
                {
                    int b = (int) pos;
                    Console.WriteLine(b);
                    List<List<int>> result = new List<List<int>>();
                    if (b + 1 > splitedStart.Count())
                    {
                        result.Add(splitedStart[b]);
                    }
                    else if (b + 1 < splitedStart.Count())
                    {
                        result.Add(MergeVectors(splitedStart[b], splitedStart[b + 1]));
                    }

                    mutex.WaitOne();
                    foreach (List<int> part in result)
                    {
                        temp.Add(part);
                    }
                    mutex.ReleaseMutex();
                   
                };
                Thread thread = new Thread(del);
                thread.Start(i);

                m_simpleThreadPool.Add(thread);
		    }
		    foreach (Thread thread in m_simpleThreadPool)
		    {
			    if (thread.IsAlive)
			    {
				    thread.Join();
			    }
		    }
		    splitedStart = temp;
	    }
	    return splitedStart[0];
    }

}
