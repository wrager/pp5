#include "stdafx.h"
#include "Thread—ryptographer.h"
#include <thread>


CThread—ryptographer::CThread—ryptographer(std::vector<char>& message, CAlphabet alphabet)
{
	m_message = —Message(message, alphabet);
	m_countThreads = std::thread::hardware_concurrency();

}

void MediatorCaesar(CThread—ryptographer * cryptographer, size_t num, int key)
{
	cryptographer->DivisionMessage(num, key);
}

void MediatorGamma(CThread—ryptographer * cryptographer, size_t num, const std::string & gamma)
{
	cryptographer->DivisionMessage(num, gamma);
}

void CThread—ryptographer::DivisionMessage(size_t threadNumber, int key)
{
	auto size = m_message.GetSize();
	size_t minSize = size / m_countThreads * threadNumber;
	size_t maxSize = (threadNumber == (m_countThreads - 1) ? size : minSize + size / m_countThreads);
	m_message.CondingForCaesar(std::make_pair(minSize, maxSize), key);

}

void CThread—ryptographer::DivisionMessage(size_t threadNumber, const std::string& gamma)
{
	auto size = m_message.GetSize();
	size_t minSize = size / m_countThreads * threadNumber;
	size_t maxSize = (threadNumber == (m_countThreads - 1) ? size : minSize + size / m_countThreads);
	m_message.CondingForGamma(std::make_pair(minSize, maxSize), gamma);
}

void CThread—ryptographer::EncipherCaesar(const int key)
{
	std::vector<std::thread> hThreads;
	hThreads.resize(m_countThreads);

	for (size_t i = 0; i <= m_countThreads - 1; ++i)
	{
		hThreads[i] = std::thread(MediatorCaesar, this, i, key);
	}
	for (auto &it : hThreads)
	{
		it.join();
	}
}

void CThread—ryptographer::EncipherGamma(const std::string& gamma)
{
	std::vector<std::thread> hThreads;
	hThreads.resize(m_countThreads);
	if (gamma != "")
	{
		for (size_t i = 0; i <= m_countThreads - 1; ++i)
		{
			hThreads[i] = std::thread(MediatorGamma, this, i, gamma);
		}
		for (auto &it : hThreads)
		{
			it.join();
		}
	}
}

std::vector<char> CThread—ryptographer::GetCharMessage() const
{
	return  m_message.GetCharMessage();
}

CThread—ryptographer::~CThread—ryptographer()
{
}
