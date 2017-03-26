// LAB6.cpp: îïğåäåëÿåò òî÷êó âõîäà äëÿ êîíñîëüíîãî ïğèëîæåíèÿ.
//

#include "stdafx.h"
#include "Alphabet.h"
#include "ÑMessage.h"
#include "LineÑryptographer.h"
#include "ThreadÑryptographer.h"

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

	std::vector<int> ConvertCharToInt(const std::vector<char> & message, std::map<char, int> & alphabet)
	{
		std::vector<int> messageCode;
		for (char symbol : message)
		{
			int codeSymbol = alphabet[symbol];
			if (codeSymbol)
			{
				messageCode.push_back(codeSymbol);
			}
		}
		return  messageCode;
	}
	
	std::vector<char> ConvertIntToChar(const std::vector<int> messageCode, std::map<char, int> & alphabet)
	{
		std::map<char, int>::const_iterator it;
		int key = 0;
		std::vector<char> message;
		for (int code : messageCode)
		{
			for (it = alphabet.begin(); it != alphabet.end(); it++)
			{
				if (it->second == code)
				{
					key = it->first;
					message.push_back(key);
					break;
				}
			}
		}
		return  message;
	}

	void ÑodingForGamma(std::vector<char> & message, std::map<char, int> alphabet, std::string gamma)
	{
		size_t sizeAlphabet = alphabet.size();
		std::vector<int> messageCode;
		for (char line : message)
		{
			messageCode.push_back(alphabet[line]);
		}
		for (size_t i = 0; i < message.size(); i++)
		{
			int iGamma = alphabet[gamma[i % gamma.size()]];
			messageCode[i] = (iGamma + messageCode[i]) % sizeAlphabet;
		}
	}

	void CondingForCaesar(std::vector<char> & message, std::map<char, int> alphabet, int key)
	{
		size_t sizeAlphabet = alphabet.size();
		std::vector<int> messageCode;
		for (char line : message)
		{
			messageCode.push_back(alphabet[line]);
		}

		for (size_t i = 0; i < message.size(); i++)
		{
			messageCode[i] = (key + messageCode[i]) % sizeAlphabet;
		}
	}
}

int main()
{
	/*
	std::string gamma;
	std::map<char, int> alphabet = ReadAlphabetFormFile("alphabet_eng.txt");
	std::vector<char> message = ReadMessageFromFile("file.txt");
	std::vector<int> code = ConvertCharToInt(message, alphabet);
	message = ConvertIntToChar(code, alphabet);
	//std::cin >> gamma;
	std::ofstream outFile("out.txt");
	for (auto i : message)
	{
		outFile.put(i);
	}
	std::cout << std::endl;
	std::cout << alphabet.size();

	CAlphabet alphabetClass;
	alphabetClass.ReadAlphabetFormFile("alphabet_eng.txt");
	int code1 = alphabetClass.GetCodeForSymbol('!');
	char c = alphabetClass.GetSymbolForCode(code1);
	code1 = alphabetClass.GetCodeForSymbol('@');
	c = alphabetClass.GetSymbolForCode(code1);
	*/
	
	CAlphabet alphabet;
	alphabet.ReadAlphabetFormFile("alphabet_eng.txt");
	std::vector<char> ms = ReadMessageFromFile("file.txt");
	for (auto i : ms)
	{
		std::cout.put(i);
	}
	std::cout << std::endl;
	for (auto i : ms)
	{
		std::cout.put(i);
	}
	std::cout << std::endl;
	CThreadÑryptographer thread_ñryptographer(ms, alphabet);
	thread_ñryptographer.EncipherCaesar(5);

	for (auto i : thread_ñryptographer.GetMessage())
	{
		std::cout.put(i);
	}
	std::cout << std::endl;
    return 0;
}