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
			flag_lock_.test_and_set(std::memory_order_acquire);
	}

	template <typename _Func, typename... Args>
	void spin(_Func f, Args&&... args) noexcept
	{
		++spin_count_;
		lock_();
		while (lock_())
		{
			f(std::forward<Args>(args)...);
		}
	}

	void spin() noexcept
	{
		++spin_count_;
		lock_();
		while (lock_()) {}
	}

	void release() noexcept
	{
		flag_lock_.clear();
	}

	void release_all() noexcept
	{
		while (spin_count_ > 0)
		{
			release();
			--spin_count_;
		}
	}

private:
	std::atomic_flag flag_lock_{ ATOMIC_FLAG_INIT };
	size_t spin_count_{ 0 };

	bool lock_() noexcept
	{
		return flag_lock_.test_and_set(std::memory_order_acquire);
	}
};

using Spin_lock = Non_copyable<Spin_lock_>;

_HULU_END

#endif // _HULU_THREAD_SPIN_LOCK_H_