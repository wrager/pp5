#pragma once
#include "Alphabet.h"
#include "—Message.h"

class CThread—ryptographer
{
public:
	CThread—ryptographer(std::vector<char> & message, CAlphabet alphabet);
	void DivisionMessage(size_t threadNumber, int key);
	void DivisionMessage(size_t threadNumber, const std::string & gamma);
	void EncipherCaesar(const int key);
	void EncipherGamma(const std::string & gamma);
	std::vector<char> GetCharMessage() const;
	~CThread—ryptographer();
private:
	size_t m_countThreads;
	std::vector<int> m_threads;
	—Message m_message;
};

