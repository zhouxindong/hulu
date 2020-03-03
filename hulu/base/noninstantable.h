#pragma once
#ifndef _HULU_BASE_NONINSTANTABLE_H_
#define _HULU_BASE_NONINSTANTABLE_H_

#include "../gvals.h"
#include <type_traits>

_HULU_BEGIN

/**
* @brief base chain wrapped the class can't be instanted
* @usage Non_instantable<class>
*/
template <class _Base>
struct Non_instantable : public _Base
{
	template <typename... _Args,
			  typename = std::enable_if_t<false>>
	explicit Non_instantable(_Args&&... args) noexcept
		: _Base(std::forward<_Args>(args)...)  {}
};

_HULU_END

#endif // _HULU_BASE_NONINSTANTABLE_H_