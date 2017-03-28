#pragma once

 

class CCompressor
{
public:
	CCompressor();
	void SetTextFragment(char * text);
	void SetLengthFragment(size_t length);
	void EditFragment();
	void Output();
	~CCompressor();
private:
	bool IsPunctuaion(char c);
	bool IsSpecials(char c);
	void DeleteOldFragment();
private:
	char * m_pTextFragment = nullptr;
	size_t m_length;
	std::unordered_map<std::string, size_t> m_dictionary;
	std::string m_textFragmentAfterProcessing;
	std::vector<char> m_punctuation;
	std::vector<char> m_specials;
};