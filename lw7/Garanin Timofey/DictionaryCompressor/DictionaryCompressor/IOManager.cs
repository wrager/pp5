using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.IO.MemoryMappedFiles;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace DictionaryCompressor
{
    class IOManager
    {
        private String m_inputFileName;
        private String m_outputFileName;
        private String m_dictionaryFileName;
        private int m_innerCount;
        private int m_roundMemoryMappingFile;
        private bool m_isFileCompletelyReadOut;
        private MemoryMappedFile m_memoryMappedFile;
        private uint m_viewLength;
        private long m_remainderLengthOfFileNotRead;
        private long m_remainderLengthOfReadFragment;
        
        public IOManager(string inputFileName, string outputFileName)
        {
            m_inputFileName = inputFileName;
            m_outputFileName = outputFileName;
            m_dictionaryFileName = "dictionary.txt";
            m_innerCount = 0;
            m_roundMemoryMappingFile = 0;
            m_isFileCompletelyReadOut = false;
            m_memoryMappedFile = null;
        }

        public int GetOrder()
        {
            return m_innerCount;
        }

        public void OutputDictionary(Dictionary<string, string> dictionary)
        {
            using (StreamWriter sw = new StreamWriter(m_dictionaryFileName, false, System.Text.Encoding.Default))
            {
                foreach (var item in dictionary)
                {
                    sw.WriteLine(item.Key + ":" + item.Value);
                }
            }
        }

        public void OutputProcessedText(string text)
        {
            using (StreamWriter sw = new StreamWriter(m_outputFileName, false, System.Text.Encoding.Default))
            {
                sw.WriteLine(text);
            }
        }

        public void SetInputFileName(string name)
        {
	        m_inputFileName = name;
        }

        public void SetOutputFileName(string name)
        {
            m_outputFileName = name;
        }

        public uint GetSizeView()
        {
	        return m_viewLength;
        }

        public bool IsFileCompletelyReadOut()
        {
	        return m_isFileCompletelyReadOut;
        }

        public void SettingInputFile()
        {
            try
            {
                CreateMemoryMappingFile();
            }
            catch(Exception ex)
            {
                throw ex;
            }
        }

        public string GetViewMappingFile()
        {
            try
            {
                if (m_remainderLengthOfReadFragment < 0)
                {
                    throw new TaskCanceledException("File ended!");
                }
                int allocationGranularity = 65536;
                string data;
                if (m_remainderLengthOfReadFragment < allocationGranularity)
                {
                    data = GetContent(allocationGranularity * m_innerCount++, m_remainderLengthOfReadFragment);
                    m_viewLength = (uint)m_remainderLengthOfReadFragment;
                    m_isFileCompletelyReadOut = true;
                }
                else
                {
                    data = GetContent(allocationGranularity * m_innerCount++, allocationGranularity);
                    m_viewLength = (uint)allocationGranularity;
                }
                m_remainderLengthOfReadFragment -= allocationGranularity;
                System.Console.WriteLine("Accessed");
                return data;
            }
            catch(TaskCanceledException ex)
            {
                throw ex;
            }
            catch (UnauthorizedAccessException ex)
            {
                Console.WriteLine("Cannot create View Streem in mapping memory file");
                throw ex;
            }
        }

        private void CreateMemoryMappingFile()
        {
            try
            {
               
                m_remainderLengthOfFileNotRead = new System.IO.FileInfo(m_inputFileName).Length;

                m_remainderLengthOfReadFragment = m_remainderLengthOfFileNotRead;
                ulong availPhys = 0;
                MEMORYSTATUSEX memStatus = new MEMORYSTATUSEX();
                GlobalMemoryStatusEx(memStatus);
                availPhys = memStatus.ullTotalPhys;
                ulong twentyPercentOfAvailPhys = availPhys / 5;
                long size = 0;
                if ((ulong)m_remainderLengthOfReadFragment < twentyPercentOfAvailPhys)
                {
                    size = m_remainderLengthOfReadFragment;
                    m_remainderLengthOfFileNotRead = 0;
                    
                }
                else
                {
                    size = (long)twentyPercentOfAvailPhys;
                    m_remainderLengthOfFileNotRead -= (long)twentyPercentOfAvailPhys;
                }
                m_memoryMappedFile = MemoryMappedFile.CreateFromFile(m_inputFileName, FileMode.Open, "FileForMapping", size);
            }
            catch (ArgumentException ex)
            {
                System.Console.WriteLine("Argument exception: " + ex.ToString());
                throw ex;
            }
            catch (IOException ex)
            {
                System.Console.WriteLine("Error: " + ex.ToString());
                throw ex;
            }
        }

        private string GetContent(long beginningByteLocation, long bytesToReadIn)
        {
            try
            { 
                string content;

                using (var memoryMappedViewStream = m_memoryMappedFile.CreateViewStream(beginningByteLocation, bytesToReadIn, MemoryMappedFileAccess.Read))
                {
                    var contentArray = new byte[bytesToReadIn];
                    memoryMappedViewStream.Read(contentArray, 0, contentArray.Length);
                    content = Encoding.UTF8.GetString(contentArray);
                }

                return content;
            }
            catch(UnauthorizedAccessException ex)
            {
                throw ex;
            }
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        private class MEMORYSTATUSEX
        {
            public uint dwLength;
            public uint dwMemoryLoad;
            public ulong ullTotalPhys;
            public ulong ullAvailPhys;
            public ulong ullTotalPageFile;
            public ulong ullAvailPageFile;
            public ulong ullTotalVirtual;
            public ulong ullAvailVirtual;
            public ulong ullAvailExtendedVirtual;
            public MEMORYSTATUSEX()
            {
                this.dwLength = (uint)Marshal.SizeOf(typeof(MEMORYSTATUSEX));
            }
        }

        [return: MarshalAs(UnmanagedType.Bool)]
        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        static extern bool GlobalMemoryStatusEx([In, Out] MEMORYSTATUSEX lpBuffer);

    }
}
