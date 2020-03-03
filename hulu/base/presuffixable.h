#pragma once
#ifndef _HULU_BASE_PRESUFFIXABLE_H_
#define _HULU_BASE_PRESUFFIXABLE_H_

#include "../gvals.h"
#include <mutex>

_HULU_BEGIN

/**
* @brief wrap prefix and suffix call for class member call 
* @usage
*/
template <typename _T, typename _Pref, typename _Suf>
class Pre_suffixable;

/**
 * @brief the class implement suffix call, use destructor
 */
template <typename _T, typename _Suf>
class Suffix_proxy
{
	_T* p_;
	mutable bool own_;
	_Suf suffix_;

	Suffix_proxy(_T* pp, _Suf su) noexcept : p_(pp), own_(true), suffix_(su) {} //restrict creation

public:
	Suffix_proxy& operator = (Suffix_proxy const&) = delete;

	template <typename U, typename P, typename S> 
	friend class Pre_suffixable;

	Suffix_proxy(Suffix_proxy const& a) noexcept :
		p_(a.p_), own_(true), suffix_(a.suffix_)
	{
		a.own_ = false;
	}

	~Suffix_proxy() noexcept
	{
		if (own_) suffix_();
	}

	_T* operator -> () const noexcept
	{
		return p_;
	}
};

/**
 * @brief wrapped type T, any call inserted _Pref and _Suf
 *		  _Pref and _Suf -> void(void)
 */
template <typename _T, typename _Pref, typename _Suf>
class Pre_suffixable
{
	_T* p_;
	int* owned_;
	void incr_owned() const noexcept
	{
		if (owned_) ++*owned_;
	}

	void decr_owned() const noexcept
	{
		if (owned_ && --*owned_ == 0)
		{
			delete p_;
			delete owned_;
		}
	}

	_Pref prefix_;
	_Suf suffix_;

public:
	Pre_suffixable(_T& x, _Pref pr, _Suf su) noexcept
		:p_(&x), owned_(nullptr), prefix_(pr), suffix_(su) {}

	Pre_suffixable(_T* pp, _Pref pr, _Suf su) noexcept
		:p_(pp), owned_(new int(1)), prefix_(pr), suffix_(su) {}

	Pre_suffixable(Pre_suffixable const& a) noexcept
		:p_(a.p_), owned_(a.owned_), prefix_(a.prefix_), suffix_(a.suffix_)
	{
		incr_owned();
	}

	Pre_suffixable& operator = (Pre_suffixable const& a) noexcept
	{
		a.incr_owned();
		decr_owned();
		p_ = a.p_;
		owned_ = a.owned_;
		prefix_ = a.prefix_;
		suffix_ = a.suffix_;
		return *this;
	}

	~Pre_suffixable() noexcept
	{
		decr_owned();
	}

	Suffix_proxy<_T, _Suf> operator-> () const noexcept
	{
		prefix_();
		return Suffix_proxy<_T, _Suf>(p_, suffix_);
	}

	_T* direct() const noexcept	// extract pointer to wrapped object
	{
		return p_;
	}
};

/**
 * a demo for wrap a single type
 */
inline
void 
trace_demo_on()
{
}

inline
void
trace_demo_off()
{
}

template <typename _T>
struct tracer : public Pre_suffixable<_T, void(*)(), void(*)()>
{
	tracer(_T& x) 
		: Pre_suffixable<_T, void(*)(), void(*)()>(x, trace_demo_on, trace_demo_off)
	{}
};

/**
 * @brief 
 */
struct Lockfixable
{
	bool prefix() noexcept
	{
		if (locked_)
			return false;

		mutex_.lock();
		locked_ = true;
		return true;
	}

	void suffix() noexcept
	{
		if (locked_)
			mutex_.unlock();
		locked_ = false;
	}

	~Lockfixable() noexcept
	{
		if (locked_)
			mutex_.unlock();
	}

private:
	std::mutex mutex_;
	bool locked_{ false };
};

struct Nonfixable
{
	bool prefix() noexcept
	{
		return true;
	}

	void suffix() noexcept
	{
	}
};

_HULU_END

#endif // _HULU_BASE_PRESUFFIXABLE_H_