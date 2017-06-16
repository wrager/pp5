using System;
using System.Threading;
using System.Collections.Generic;

namespace DictionaryCompressor
{
	class Application
	{
		private IOManager m_iomanager;
		private RepositoryProcessedData m_myRepository;
		private int m_nextThreadOrderForWrite;
		private List<Thread> m_threads;
		private Mutex m_mutex;
		private Mutex m_mutexForCompressor;

		public Application(IOManager manager)
		{
			m_iomanager = manager;
			m_nextThreadOrderForWrite = 0;
			m_myRepository = new RepositoryProcessedData();
			m_threads = new List<Thread>();
			m_mutex = new Mutex();
			m_mutexForCompressor = new Mutex();
		}

		public void SetInputFileName(string name)
		{
			m_iomanager.SetInputFileName(name);
		}
		public void SetOutputFileName(string name)
		{
			m_iomanager.SetOutputFileName(name);
		}

		public void ProcessFile()
		{
			try
			{
				
				while (!m_iomanager.IsFileCompletelyReadOut())
				{
					m_iomanager.SettingInputFile();
					for (uint i = 0; i != Environment.ProcessorCount; ++i)
					{
						var thread = new Thread(ProcessNextFragment);
						thread.Start();

						m_threads.Add(thread);

					}

					foreach (var thread in m_threads)
					{
						if (thread.IsAlive)
						{
							thread.Join();
						}
					}

					m_threads.RemoveRange(0, m_threads.Count);
				}
				System.Console.WriteLine("File processed");
				return;
			}
			catch (Exception ex)
			{
			   System.Console.WriteLine("Error! " + ex.ToString());
				return;
			}
		}

		private void SaveNewInformation(Compressor compressor)
		{
			m_myRepository.SetNewTextFragment(compressor.GetAllProcessingText());
		}

		public void SaveResultsInFile()
		{
			m_iomanager.OutputDictionary(m_myRepository.GetDictionary());
			m_iomanager.OutputProcessedText(m_myRepository.GetText());
		}

		private void ProcessNextFragment()
		{
			var success = true;
			while (success)
			{
				try
				{
					m_mutex.WaitOne();
					Compressor compressor = new Compressor(m_iomanager.GetOrder(), m_myRepository, m_mutexForCompressor);
					var dataPtr = m_iomanager.GetViewMappingFile();
					m_mutex.ReleaseMutex();
					compressor.SetTextFragment(dataPtr);
					compressor.SetLengthFragment(m_iomanager.GetSizeView());
					compressor.EditFragment();

					while (true)
					{
						if (compressor.GetOrder() == m_nextThreadOrderForWrite)
						{
							m_mutex.WaitOne();
							SaveNewInformation(compressor);
							m_mutex.ReleaseMutex();
							++m_nextThreadOrderForWrite;
							break;
						}
						else
						{
							Thread.Sleep(1000);
						}
					}
				}
				catch (Exception)
				{
					m_mutex.ReleaseMutex();
					success = false;
				}
			}
		}
	}
}
