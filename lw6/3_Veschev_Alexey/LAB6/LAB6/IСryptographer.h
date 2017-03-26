#pragma once
#include "ÑMessage.h"
class IÑryptographer
{
public:
	IÑryptographer() = default;
	virtual ~IÑryptographer() {};
protected:
	virtual void EncipherCaesar() = 0;
	virtual void EncipherGamma() = 0;
	ÑMessage m_message;
};

