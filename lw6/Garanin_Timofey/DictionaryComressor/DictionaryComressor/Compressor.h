#pragma once

 

class CCompressor
{
public:
	CCompressor();
	void SetTextFragment(char * text);
	void SetLengthFragment(size_t length);
	void EditFragment();
	std::shared_ptr<std::unordered_map<std::string, size_t>> GetAllDictionary() const;
	std::shared_ptr<std::string> GetAllProcessingText();
private:
	bool IsPunctuaion(char c);
	bool IsSpecials(char c);
private:
	char * m_pTextFragment = nullptr;
	size_t m_length;
	std::shared_ptr<std::unordered_map<std::string, size_t>> m_dictionary = nullptr;
	std::shared_ptr<std::string> m_textFragmentAfterProcessing = nullptr;
	std::vector<char> m_punctuation;
	std::vector<char> m_specials;
	std::string m_incompleteWord;
};