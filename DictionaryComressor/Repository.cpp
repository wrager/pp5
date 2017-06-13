#include "stdafx.h"
#include "Repository.h"

CRepository::CRepository()
{
	m_dictionary = std::make_shared<std::unordered_map<std::string, std::string>>();
	m_resultText = std::make_shared<std::string>();
}

void CRepository::SetNewDictionaryFragment(std::shared_ptr<std::unordered_map<std::string, std::string>> fragment)
{
	m_dictionary = fragment;
}

void CRepository::SetNewTextFragment(std::shared_ptr<std::string> text)
{
	m_resultText->insert(m_resultText->end(), text->begin(), text->end());
}

std::shared_ptr<std::unordered_map<std::string, std::string>> CRepository::GetDictionary() const
{
	return m_dictionary;
}

std::shared_ptr<std::string> CRepository::GetText() const
{
	return m_resultText;
}
