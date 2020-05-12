#pragma once
#ifndef _HULU_THREAD_SPIN_LOCK_H_
#define _HULU_THREAD_SPIN_LOCK_H_

#include "../gvals.h"

#include <atomic>

#include "base/noncopyable.h"

_HULU_BEGIN

/**
 * @brief use atomic_flag to implement a spin lock
 * @note .test_and_set() set value to true, and return old value
 * @note .clear() set value to false
 */	

class Spin_lock_
{
public:
	Spin_lock_(bool setable = true) noexcept
	{
		if (setable)
			flag_lock_.test_and_set(std::memory_order_relaxed);
	}

	template <typename _Func, typename... Args>
	void spin(_Func&& f, Args&&... args) noexcept
	{
		lock_();
		while (lock_() && !released_)
		{
			std::forward<_Func>(f)(std::forward<Args>(args)...);
		}
	}

	void spin() noexcept
	{
		lock_();
		while (lock_() && !released_) {}
	}

	void release() noexcept
	{
		flag_lock_.clear();
		released_ = true;
	}

private:
	std::atomic_flag flag_lock_{ ATOMIC_FLAG_INIT };
	bool released_{ false };

	bool lock_() noexcept
	{
		return flag_lock_.test_and_set(std::memory_order_relaxed);
	}
};

using Spin_lock = Non_copyable<Spin_lock_>;

_HULU_END

#endif // _HULU_THREAD_SPIN_LOCK_H_