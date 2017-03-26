#include "stdafx.h"
#include "Alphabet.h"


CAlphabet::CAlphabet()
{
}

void CAlphabet::ReadAlphabetFormFile(const std::string fileName)
{
	m_alphabet.clear();
	typedef std::istreambuf_iterator<char> buf_iter;
	std::fstream file(fileName);
	int count = 0;
	for (buf_iter i(file), e; i != e; ++i)
	{
		char c = *i;
		m_alphabet.insert(std::make_pair(c, count++));
	}
}

int CAlphabet::GetCodeForSymbol(const char& symbol)
{
	std::map<char, int>::iterator it = m_alphabet.find(symbol);
	if (it != m_alphabet.end())
	{
		return it->second;
	}
	return  -1;
}
	

char CAlphabet::GetSymbolForCode(const int code)
{
	int key = -1;
	std::map<char, int>::const_iterator it;
	for (it = m_alphabet.begin(); it != m_alphabet.end(); it++)
	{
		if (it->second == code)
		{
			return it->first;
		}
	}
	return '-';
}


CAlphabet::~CAlphabet()
{
}

size_t CAlphabet::GetSize() const
{
	return  m_alphabet.size();
}
