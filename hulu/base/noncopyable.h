#pragma once
#ifndef _HULU_BASE_NONCOPYABLE_H_
#define _HULU_BASE_NONCOPYABLE_H_

#include "../gvals.h"
#include <type_traits>

_HULU_BEGIN

/**
* @brief base chain wrapped the class can't be copy construct or assignment
* @usage Non_copyable<class>
*/
template <typename _Base>
struct Non_copyable : public _Base
{
	explicit Non_copyable() = default;

	template <typename... _Args,
		typename = std::enable_if_t<sizeof...(_Args) != 1>>
		explicit Non_copyable(_Args&&... args) noexcept
		: _Base(std::forward<_Args>(args)...)  {}

	template <typename Arg,
		typename = std::enable_if_t<
		!std::is_same_v<Non_copyable, std::decay_t<Arg>>>>
		explicit Non_copyable(Arg&& arg) noexcept
		: _Base(std::forward<Arg>(arg))  {}

	Non_copyable(Non_copyable const&) = delete;
	Non_copyable& operator = (Non_copyable const&) = delete;

	Non_copyable(Non_copyable&&) = default;
	Non_copyable& operator = (Non_copyable&&) = default;
};


_HULU_END

#endif // _HULU_BASE_NONCOPYABLE_H_