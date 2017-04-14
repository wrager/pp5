#pragma once
#include <functional>

using TaskBody = std::function<void()>;

class IAsyncManager
{
public:
	virtual ~IAsyncManager() = default;
	virtual void Post(TaskBody const& task) = 0;
};