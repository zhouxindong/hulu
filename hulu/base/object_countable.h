#pragma once
#ifndef _HULU_BASE_OBJECT_COUNTABLE_H_
#define _HULU_BASE_OBJECT_COUNTABLE_H_

#include "../gvals.h"

_HULU_BEGIN

/**
 * @brief provide the Type can count it's objects
 */
template <typename _Counted_type>
class Object_countable : public _Counted_type
{
private:
	static std::size_t s_count;

public:
	template <typename... Args>
	Object_countable(Args&&... args) noexcept
		: _Counted_type(std::forward<Args>(args)...) 
	{
		++s_count;
	}

	~Object_countable() noexcept
	{
		--s_count;
	}

	static size_t live() noexcept
	{
		return s_count;
	}
};

template <typename _Counted_type>
size_t Object_countable<_Counted_type>::s_count = 0;

_HULU_END

#endif // _HULU_BASE_OBJECT_COUNTABLE_H_