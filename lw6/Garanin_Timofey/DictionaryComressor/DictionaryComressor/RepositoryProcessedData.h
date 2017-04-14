#pragma once

class CRepositoryProcessedData
{
public:
	CRepositoryProcessedData();
	void SetNewDictionaryFragment(std::shared_ptr<std::unordered_map<std::string, std::string>> dictionaryFragment);
	void SetNewTextFragment(std::shared_ptr<std::string> text);
	std::shared_ptr<std::unordered_map<std::string, std::string>> GetDictionary() const;
	std::shared_ptr<std::string> GetText() const;
private:
	std::shared_ptr<std::unordered_map<std::string, std::string>> m_dictionary;
	std::shared_ptr<std::string> m_text;
};