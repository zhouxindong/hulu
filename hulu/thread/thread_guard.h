#pragma once

#ifndef _HULU_THREAD_THREAD_GUARD_H_
#define _HULU_THREAD_THREAD_GUARD_H_

#include "../gvals.h"

#include <thread>

_HULU_BEGIN

class Thread_guard
{
	std::thread& t_;

public:
	explicit Thread_guard(std::thread& t) : t_(t) {}

	~Thread_guard()
	{
		if (t_.joinable())
			t_.join();
	}

	Thread_guard(const Thread_guard&) = delete;
	Thread_guard& operator = (const Thread_guard&) = delete;
};

_HULU_END

#endif // _HULU_THREAD_THREAD_GUARD_H_