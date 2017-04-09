#include "stdafx.h"
#include "Repository.h"

CMyRepository::CMyRepository()
{
	m_dictionary = std::make_shared<std::unordered_map<std::string, std::string>>();
	m_text = std::make_shared<std::string>();
}

void CMyRepository::SetNewDictionaryFragment(std::shared_ptr<std::unordered_map<std::string, std::string>> dictionaryFragment)
{
	m_dictionary = dictionaryFragment;
}

void CMyRepository::SetNewTextFragment(std::shared_ptr<std::string> text)
{
	m_text->insert(m_text->end(), text->begin(), text->end());
}

std::shared_ptr<std::unordered_map<std::string, std::string>> CMyRepository::GetDictionary() const
{
	return m_dictionary;
}

std::shared_ptr<std::string> CMyRepository::GetText() const
{
	return m_text;
}
