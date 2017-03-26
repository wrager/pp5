#include "stdafx.h"
#include "Line—ryptographer.h"
#include "—Message.h"


CLine—ryptographer::CLine—ryptographer(std::vector<char> & message, CAlphabet alphabet)
{
	m_message = —Message(message, alphabet);
}

CLine—ryptographer::~CLine—ryptographer()
{

}


void CLine—ryptographer::EncipherCaesar(const int key)
{
	m_message.CondingForCaesar(std::make_pair(0, m_message.GetSize()), key);
}

void CLine—ryptographer::EncipherGamma(const std::string & gamma)
{
	m_message.CondingForGamma(std::make_pair(0, m_message.GetSize()), gamma);
}

std::vector<char> CLine—ryptographer::GetMessage() const
{
	return  m_message.GetMessage();
}