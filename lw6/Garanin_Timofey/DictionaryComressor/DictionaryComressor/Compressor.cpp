#include "stdafx.h"
#include "Repository.h"
#include "Compressor.h"
#include <cctype>
#include <algorithm>
#include <sstream>
#include <stdlib.h>

CCompressor::CCompressor(size_t order, CMyRepository *repository, std::mutex *mutex)
{
	m_mutex = mutex;
	m_order = order;
	m_repository = repository;
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

				m_mutex->lock();
				auto dict = m_repository->GetDictionary();
				if (dict->count(word) > 0)
				{
					
					number = std::stoi(dict->at(word));
					ss << number;
				}
				else
				{
					number = static_cast<int>(dict->size());
					ss << number;
					dict->insert(std::pair<std::string, std::string>(word, std::string(ss.str())));
				}
				m_mutex->unlock();
				
				std::string cv = std::string(ss.str());
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

size_t CCompressor::GetOrder()
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
