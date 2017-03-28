// LAB6.cpp: îïğåäåëÿåò òî÷êó âõîäà äëÿ êîíñîëüíîãî ïğèëîæåíèÿ.
//

#include "stdafx.h"
#include "Alphabet.h"
#include "LineÑryptographer.h"
#include "ThreadÑryptographer.h"
#include <ctime>

namespace
{
	std::map<char, int> ReadAlphabetFormFile(const std::string fileName)
	{
		typedef std::istreambuf_iterator<char> buf_iter;
		std::fstream file(fileName);
		std::map<char, int> alphabet;
		int count = 1;
		for (buf_iter i(file), e; i != e; ++i) 
		{
			char c = *i;
			alphabet.insert(std::make_pair(c, count++));
		}
	
		return alphabet;
	}

	std::vector<char> ReadMessageFromFile(const std::string fileName)
	{
		typedef std::istreambuf_iterator<char> buf_iter;
		std::fstream file(fileName);
		std::vector<char> mass;
		for (buf_iter i(file), e; i != e; ++i)
		{
			char c = *i;
			mass.push_back(c);
		}

		return mass;
	}

	void WriteMessageFromFile(std::vector<char> & message)
	{
		std::ofstream outFile("out.txt");
		for (auto i : message)
		{
			outFile.put(i);
		}
	}

	void EncipherCaesar(const std::string & alphabetStr, const std::string & fileStr, const int key)
	{
		CAlphabet alphabet;
		alphabet.ReadAlphabetFormFile(alphabetStr);
		clock_t begin;
		clock_t end;
		double elapsedSecsParallel;
		std::vector<char> messageForLiner = ReadMessageFromFile(fileStr);
		std::vector<char> messageForThread = messageForLiner;
		CLineÑryptographer liner_ñryptographer(messageForLiner, alphabet);
		CThreadÑryptographer thread_ñryptographer(messageForThread, alphabet);
		std::cout << "Start Encipher Caesar" << std::endl;
		begin = clock();
		liner_ñryptographer.EncipherCaesar(key);
		end = clock();
		elapsedSecsParallel = double(end - begin) / CLOCKS_PER_SEC;
		std::cout << elapsedSecsParallel << " For liner" << std::endl;
		begin = clock();
		thread_ñryptographer.EncipherCaesar(key);
		end = clock();
		elapsedSecsParallel = double(end - begin) / CLOCKS_PER_SEC;
		std::cout << elapsedSecsParallel << " for thread" << std::endl;
	}

	void EncipherGamma(const std::string & alphabetStr, const std::string & fileStr, const std::string & gamma)
	{
		CAlphabet alphabet;
		alphabet.ReadAlphabetFormFile(alphabetStr);
		clock_t begin;
		clock_t end;
		double elapsedSecsParallel;
		std::vector<char> messageForLiner = ReadMessageFromFile(fileStr);
		std::vector<char> messageForThread = messageForLiner;
		CLineÑryptographer liner_ñryptographer(messageForLiner, alphabet);
		CThreadÑryptographer thread_ñryptographer(messageForThread, alphabet);
		std::cout << "Start Encipher Gamma" << std::endl;
		begin = clock();
		liner_ñryptographer.EncipherGamma(gamma);
		end = clock();
		elapsedSecsParallel = double(end - begin) / CLOCKS_PER_SEC;
		std::cout << elapsedSecsParallel << " For liner" << std::endl;
		begin = clock();
		thread_ñryptographer.EncipherGamma(gamma);
		end = clock();
		elapsedSecsParallel = double(end - begin) / CLOCKS_PER_SEC;
		std::cout << elapsedSecsParallel << " for thread" << std::endl;
	}
}

int main()
{
	int key = 0;
	
	std::cout << "Key for Gamma Encipher = ";
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	std::string gamma = "";
	getline(std::cin, gamma);
	SetConsoleMode(hStdin, mode);
	std::cout << std::endl;
	std::cout << "Key for Caesar Encipher = ";
	std::cin >> key;
	std::cout << std::endl;
	
	EncipherGamma("alphabet_eng.txt", "Harry_Potter_1.txt", gamma);
	EncipherCaesar("alphabet_eng.txt", "Harry_Potter_1.txt", key);

	std::cout << std::endl;
    return 0;
}