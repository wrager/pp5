#include "stdafx.h"
#include "Compressor.h"
#include <cctype>
#include <algorithm>
#include <sstream>
#include <stdlib.h>

static const int RESERVED_NUMBER_WORDS = 5000;


CCompressor::CCompressor(size_t order)
{
	m_order = order;
	m_punctuation = { ',', '.', ';', ':', '?', '!', '-', '(', ')', '\'', '\"', ' ' };
	m_specials = { '\n', '\t', '\r', '\f', '\b' };
	m_dictionary = std::make_shared<std::unordered_map<std::string, std::string>>();
	m_textFragmentAfterProcessing = std::make_shared<std::string>();
}

void CCompressor::SetTextFragment(char * text)
{
	m_pTextFragment = text;
}

void CCompressor::SetLengthFragment(size_t length)
{
	m_length = length;
}

void CCompressor::EditFragment()
{
	std::string word;
	if (!m_incompleteWord.empty())
	{
		word = m_incompleteWord;
		m_incompleteWord.clear();
	}
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
			if (!ifPastWasPunctMark)
			{
				int number = 0;
				std::transform(word.begin(), word.end(), word.begin(), ::tolower);
				std::stringstream ss;
				
				std::string cv("");
				if (m_dictionary->count(word) > 0)
				{
					number = std::stoi(m_dictionary->at(word));
					ss << number;
				}
				else
				{
					number = m_order * RESERVED_NUMBER_WORDS + m_dictionary->size();
					ss << number;
					m_dictionary->insert(std::pair<std::string, std::string>(word, std::string(ss.str())));
				}
				cv = std::string(ss.str());
				

				m_textFragmentAfterProcessing->insert(m_textFragmentAfterProcessing->end(), cv.begin(), cv.end());
				if (!IsSpecials(m_pTextFragment[i]))
				{
					m_textFragmentAfterProcessing->insert(m_textFragmentAfterProcessing->end(), m_pTextFragment[i]);
				}
				ifPastWasPunctMark = true;
				word.clear();
			}
			else if (!IsSpecials(m_pTextFragment[i]))
			{
				m_textFragmentAfterProcessing->push_back(m_pTextFragment[i]);
			}
		}
		if (IsSpecials(m_pTextFragment[i]))
		{
			m_textFragmentAfterProcessing->push_back(m_pTextFragment[i]);
			word.clear();
		}
	}
	if (!word.empty())
	{
		m_incompleteWord = std::string(word);
	}
}

int CCompressor::GetOrder()
{
	return m_order;
}

std::shared_ptr<std::unordered_map<std::string, std::string>> CCompressor::GetAllDictionary() const
{
	return m_dictionary;
}

std::shared_ptr<std::string> CCompressor::GetAllProcessingText()
{
	return m_textFragmentAfterProcessing;
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
