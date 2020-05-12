#pragma once

#ifndef _HULU_UTILITY_REFLECT_H_
#define _HULU_UTILITY_REFLECT_H_

#include "../gvals.h"

#include <map>
#include <string>
#include <functional>

_HULU_BEGIN

class Reflect_base
{
public:
	virtual ~Reflect_base() noexcept {}

public:
	template <typename _Tx, typename... Args>
	_Tx* create_object(Args&&... args)
	{
		return new _Tx(std::forward<Args>(args)...);
	}	
};

template <typename _Derived>
class Curious_base : public Reflect_base
{
public:
	template <typename... Args>
	_Derived* create_object(Args&&... args)
	{
		return new _Derived(std::forward<Args>(args)...);
	}
};

_HULU_END

#endif // _HULU_UTILITY_REFLECT_H_