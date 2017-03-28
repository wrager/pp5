#include "stdafx.h"
#include "Compressor.h"
#include <cctype>
#include <algorithm>
#include <sstream>
#include <stdlib.h>


CCompressor::CCompressor()
{
	m_punctuation = { ',', '.', ';', ':', '?', '!', '-', '(', ')', '\'', '\"', ' ' };
	m_specials = { '\n', '\t', '\r', '\f', '\b' };
}

void CCompressor::SetTextFragment(char * text)
{
	DeleteOldFragment();
	m_pTextFragment = text;
}

void CCompressor::SetLengthFragment(size_t length)
{
	m_length = length;
}

void CCompressor::EditFragment()
{
	std::string word;
	bool ifPastWasPunctMark = false;
	for (size_t i = 0; i != m_length; ++i)
	{
		if (!IsPunctuaion(m_pTextFragment[i]) && !IsSpecials(m_pTextFragment[i]))
		{
			word += m_pTextFragment[i];
			ifPastWasPunctMark = false;
		}
		else
		{
			//TODO: при окончании проверки фрагмента если последнее слово не завершено то мы в следующий раз 
			//не начинаем заного а продолжаем тоже самое слово
			if (!ifPastWasPunctMark)
			{
				int number = 0;
				std::transform(word.begin(), word.end(), word.begin(), ::tolower);
				if (m_dictionary.count(word) > 0)
				{
					number = (int)m_dictionary.at(word);
				}
				else
				{
					m_dictionary.insert(std::pair<std::string, size_t>(word, m_dictionary.size()));
					number = (int)m_dictionary.size() - 1;
				}

				std::stringstream ss;
				ss << number;
				std::string cv(ss.str());

				m_textFragmentAfterProcessing.insert(m_textFragmentAfterProcessing.end(), cv.begin(), cv.end());
				if (!IsSpecials(m_pTextFragment[i]))
				{
					m_textFragmentAfterProcessing.insert(m_textFragmentAfterProcessing.end(), m_pTextFragment[i]);
				}
				ifPastWasPunctMark = true;
				word.clear();
			}
			else if (!IsSpecials(m_pTextFragment[i]))
			{
				m_textFragmentAfterProcessing.push_back(m_pTextFragment[i]);
			}
		}
		if (IsSpecials(m_pTextFragment[i]))
		{
			m_textFragmentAfterProcessing.push_back(m_pTextFragment[i]);
			word.clear();
		}
	}
}

CCompressor::~CCompressor()
{
	DeleteOldFragment();
}

bool CCompressor::IsPunctuaion(char c)
{
	auto index = std::find(m_punctuation.begin(), m_punctuation.end(), c);
	if (index == m_punctuation.end())
	{
		return false;
	}
	return true;
}

bool CCompressor::IsSpecials(char c)
{
	auto index = std::find(m_specials.begin(), m_specials.end(), c);
	if (index == m_specials.end())
	{
		return false;
	}
	return true;
}

void CCompressor::DeleteOldFragment()
{
	delete m_pTextFragment;
}
