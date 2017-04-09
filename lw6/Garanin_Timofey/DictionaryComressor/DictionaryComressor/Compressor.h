#pragma once

 

class CCompressor
{
public:
	CCompressor(size_t order, CMyRepository *repository, std::mutex *mutex);
	void SetTextFragment(char * text);
	void SetLengthFragment(size_t length);
	void EditFragment();
	size_t GetOrder();
	std::shared_ptr<std::unordered_map<std::string, std::string>> GetAllDictionary() const;
	std::shared_ptr<std::string> GetAllProcessingText();
private:
	bool IsPunctuaion(char c);
	bool IsSpecials(char c);
private:
	char * m_pTextFragment = nullptr;
	size_t m_length;
	size_t m_order;
	CMyRepository *m_repository;
	std::mutex *m_mutex;
	std::shared_ptr<std::unordered_map<std::string, std::string>> m_dictionary = nullptr;
	std::shared_ptr<std::string> m_textFragmentAfterProcessing = nullptr;
	std::vector<char> m_punctuation;
	std::vector<char> m_specials;
	std::string m_incompleteWord;
};