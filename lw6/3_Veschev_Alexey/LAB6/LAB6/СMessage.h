#pragma once
#include "Alphabet.h"
#include <memory>

class �Message
{
public:
	�Message() = default;
	�Message(std::vector<char> & message, CAlphabet alphabet);
	std::vector<char> GetCharMessage() const;
	size_t GetSize() const;
	void CondingForCaesar(std::pair<size_t, size_t> const & range, int key);
	void CondingForGamma(std::pair<size_t, size_t> const & range, std::string gamma);
	~�Message();
private:
	std::vector<char> m_message;
	std::shared_ptr<CAlphabet> ptr_alphabet;
};

