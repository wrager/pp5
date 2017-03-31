#pragma once
#include <functional>


class CUtils
{
public:
	static void CalculateFunctionTime(std::function<void()> callback);

};
