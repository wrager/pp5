#pragma once
#include "—Message.h"

class CLine—ryptographer
{
public:
	CLine—ryptographer(std::vector<char> & message, CAlphabet alphabet);
	~CLine—ryptographer();

	void EncipherCaesar(const int key);
	void EncipherGamma(const std::string & gamma);
	std::vector<char> GetMessage() const;
private:
	—Message m_message;
};

