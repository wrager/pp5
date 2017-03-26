#pragma once
#include <vector>
#include <map>
#include "Alphabet.h"
#include <memory>

class ÑMessage
{
public:
	ÑMessage() = default;
	ÑMessage(std::vector<char> message, CAlphabet & alphabet);
	std::vector<char> GetMessage() const;
	void CondingForCaesar(std::pair<size_t, size_t> const & range, CAlphabet & alphabet, int key);
	~ÑMessage();
private:
	
	void CondingForGamma(std::pair<size_t, size_t> const & range, CAlphabet & alphabet, std::string gamma);
	std::vector<char> m_message;
	std::unique_ptr<CAlphabet> ptr_alphabet;
};

