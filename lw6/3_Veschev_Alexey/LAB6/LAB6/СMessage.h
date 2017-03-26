#pragma once
#include "Alphabet.h"
#include <memory>

class ÑMessage
{
public:
	ÑMessage() = default;
	ÑMessage(std::vector<char> & message, CAlphabet alphabet);
	std::vector<char> GetMessage() const;
	size_t GetSize() const;
	void CondingForCaesar(std::pair<size_t, size_t> const & range, int key);
	void CondingForGamma(std::pair<size_t, size_t> const & range, std::string gamma);
	~ÑMessage();
private:
	std::vector<char> m_message;
	std::shared_ptr<CAlphabet> ptr_alphabet;
};

