#include "stdafx.h"
#include "GammaCoding.h"

size_t getNum(std::string const & line)
{
	std::istringstream stream(line);
	size_t num;
	stream >> num;
	return num;
}

void StartParall(CGammaCoding * code, size_t start, size_t finish)
{
	code->Parall(start, finish);
}

void CGammaCoding::Parall(size_t start, size_t finish)
{
	for (size_t i = start; i < finish; i++)
	{
		size_t countAlphabet = 0;

		for (size_t j = 0; j < m_text[i].length(); j++)
		{
			size_t ascii_code = m_text[i][j];
			size_t minSize = 1;
			if ((ascii_code > 64 && ascii_code < 91) || (ascii_code > 96 && ascii_code < 123))
			{
				if (ascii_code > 64 && ascii_code < 91)
				{
					ascii_code += alphabet[countAlphabet];
					countAlphabet = countAlphabet < alphabet.size() - 1 ? countAlphabet + 1 : 0;
					minSize = 65;
				}
				else
					if (ascii_code > 96 && ascii_code < 123)
					{
						ascii_code += alphabet[countAlphabet];
						countAlphabet = countAlphabet < alphabet.size() - 1 ? countAlphabet + 1 : 0;
						minSize = 97;
					}
				ascii_code = minSize + (ascii_code % minSize) % 26;
				m_text[i][j] = char(ascii_code);
			}
		}
	}
}

void CGammaCoding::LoadAlphabet()
{
	std::cout << "write alphabet for coding. input some numbers with Enter. For end write '...' " << std::endl;
	std::string num;
	std::cin >> num;
	while (num != "...")
	{
		size_t number = getNum(num);
		if (number != NULL)
		{
			alphabet.push_back(number);
		}
		std::cin >> num;
	}
}

void CGammaCoding::LoadText(std::ifstream & inputFile)
{
	std::string line;
	if (inputFile.is_open())
	{
		while (std::getline(inputFile, line))
		{
			m_text.push_back(line);
		}
	}
	else
	{
		std::cout << "error file";
	}
}

void CGammaCoding::WriteAnswer(std::ofstream & outputFile)
{
	for (size_t i = 0; i < m_text.size(); i++)
	{
		outputFile << m_text[i] << std::endl;
	}
}

void CGammaCoding::StartProgram(std::string const & fileName, std::string threadNumbers)
{
	maxThread = getNum(threadNumbers);
	LoadAlphabet();
	std::ifstream inputFile(fileName);
	std::ofstream outputFile1("consistent.txt");
	std::ofstream outputFile2("parall.txt");
	LoadText(inputFile);
	inputFile.close();

	std::vector<std::string> lastText = m_text;
	
	double startTime = clock() / 1000.0;
	Parall(0, m_text.size());
	double endTime = clock() / 1000.0;
	
	std::cout << "consistent method need: " << endTime - startTime << std::endl;
	
	WriteAnswer(outputFile1);
	m_text = lastText;

	startTime = clock() / 1000.0;
	DivideOnThreads();
	endTime = clock() / 1000.0;

	std::cout << "parall method need: " << endTime - startTime << std::endl;
	
	WriteAnswer(outputFile2);
}

void CGammaCoding::ClearThreadVector(std::vector<std::thread> & thrs, size_t threads)
{
	for (size_t j = 0; j < threads; j++)
	{
		thrs[j].join();
	}
}

void CGammaCoding::DivideOnThreads()
{
	maxThread = maxThread > m_text.size() ? m_text.size() : maxThread;
	size_t numForEachThread = m_text.size() / maxThread;
	std::vector<std::thread> thrs(maxThread);
	size_t currentThread = 0;
	for (size_t i = 0; i < maxThread; i++)
	{
		if (i + 1 < maxThread)
		{
			thrs[currentThread] = std::thread(StartParall, this, i * numForEachThread, i * numForEachThread + numForEachThread);
		}
		else
		{
			thrs[currentThread] = std::thread(StartParall, this, i * numForEachThread, i * numForEachThread + numForEachThread + m_text.size() % maxThread);
		}
		currentThread++;
	}
	ClearThreadVector(thrs, maxThread);
}
