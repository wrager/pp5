#pragma once
#include <map>

class CAlphabet
{
public:
	CAlphabet();
	void ReadAlphabetFormFile(const std::string fileName);
	int GetCodeForSymbol(const char & symbol);
	char GetSymbolForCode(const int code);
	size_t GetSize() const;

	~CAlphabet();
private:
	std::map<char, int> m_alphabet;
};

