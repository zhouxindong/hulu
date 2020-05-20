#pragma once
#ifndef _HULU_BASE_EASY_SIGNAL_H_
#define _HULU_BASE_EASY_SIGNAL_H_

#include "../gvals.h"

#include <functional>
#include <vector>
#include <type_traits>
#include <algorithm>

_HULU_BEGIN

/**
 * @brief a simple signal slot implement
 */
template <typename _Signature>
class Easy_signal;

template <typename _Ret, typename ..._Args>
class Easy_signal<_Ret(_Args...)>
{
public:
	void swap(Easy_signal& rhs) noexcept
	{
		std::swap(slots_, rhs.slots_);
		std::swap(signals_, rhs.signals_);
	}

public:
	Easy_signal() noexcept {}

	~Easy_signal() {}

	Easy_signal(const Easy_signal& rhs) noexcept 
		: slots_(rhs.slots_)
		, signals_(rhs.signals_)
	{		
	}

	Easy_signal(Easy_signal&& rhs) noexcept 
		: slots_(std::move(rhs.slots_))
		, signals_(std::move(rhs.signals_))
	{
	}

	Easy_signal& operator=(const Easy_signal& rhs) noexcept
	{
		Easy_signal temp(rhs);
		swap(temp);
		return *this;
	}

	Easy_signal& operator=(Easy_signal&& rhs) noexcept
	{
		Easy_signal temp(std::move(rhs));
		swap(temp);
		return *this;
	}

	/**
	 * connect slots to signal
	 1. function
	 2. functor
	 3. lambda
	 */
	template <typename _Callable>
	void connect(_Callable&& call) noexcept
	{
		using Functor = std::decay_t<_Callable>;
		slots_.push_back(std::forward<Functor>(call));
	}

	/**
	 * connect class member function to signal
	 */
	template <typename _Ret2, typename _Class>
	void connect(_Ret2 _Class::* pmf, _Class& obj)
	{
		slots_.push_back(std::bind(pmf, obj));
	}

	/**
	 * signal connect to signal
	 */
	void connect(const Easy_signal& rhs)
	{
		signals_.push_back(rhs);
	}

	/**
	 * emit signal
	 */
	void operator()(_Args&&... args) const
	{
		std::for_each(slots_.cbegin(), slots_.cend(), [](const auto& f) {
			f(std::forward<_Args>(args)...);
		});
	}

private:
	std::vector<std::function<_Ret(_Args...)>> slots_;
	std::vector<std::reference_wrapper<Easy_signal>> signals_;
};

_HULU_END

#endif /* _HULU_BASE_EASY_SIGNAL_H_ */