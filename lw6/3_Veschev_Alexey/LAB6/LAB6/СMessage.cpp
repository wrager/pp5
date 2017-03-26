#include "stdafx.h"
#include "ÑMessage.h"
#include "Alphabet.h"


ÑMessage::ÑMessage(std::vector<char> & message, CAlphabet alphabet)
{
	m_message = message;
	ptr_alphabet = std::make_shared<CAlphabet>(alphabet);
}



std::vector<char> ÑMessage::GetMessage() const
{
	return m_message;
}

size_t ÑMessage::GetSize() const
{
	return m_message.size();
}

ÑMessage::~ÑMessage()
{
}


void ÑMessage::CondingForCaesar(std::pair<size_t, size_t> const & range, int key)
{
	size_t sizeAlphabet = ptr_alphabet->GetSize();
	for (auto i = range.first; i < range.second; i++)
	{
		int codeSymbol = ptr_alphabet->GetCodeForSymbol(m_message[i]);
		codeSymbol  = (key + codeSymbol) % sizeAlphabet;
		m_message[i] = ptr_alphabet->GetSymbolForCode(codeSymbol);
	}
}

void ÑMessage::CondingForGamma(std::pair<size_t, size_t> const& range, std::string gamma)
{
	size_t sizeAlphabet = ptr_alphabet->GetSize();
	for (auto i = range.first; i < range.second; i++)
	{
		int codeSymbol = ptr_alphabet->GetCodeForSymbol(m_message[i]);
		int codeGamma = ptr_alphabet->GetCodeForSymbol(gamma[i % gamma.size()]);
		codeSymbol = (codeGamma + codeSymbol) % sizeAlphabet;
		m_message[i] = ptr_alphabet->GetSymbolForCode(codeSymbol);
	}
}
