#pragma once
#ifndef _HULU_BASE_PIPE_RANGE_H_
#define _HULU_BASE_PIPE_RANGE_H_

#include "../gvals.h"

#include <functional>
#include <type_traits>
#include <numeric>

_STD_BEGIN

/**
 * @brief map pipe
 */
template <
	template <typename, typename...> class _Cont,
	typename _R,
	typename _Tx,
	typename... _Args>
	_Cont<_R, _Args...> operator | (const _Cont<_Tx, _Args...>& v, std::function<_R(_Tx)> f)
{
	_Cont<_R, _Args...> result;
	for (const auto e : v)
		result.push_back(f(e));
	return result;
}

/**
 * @brief filter pipe
 */
template <
	template <typename, typename...> class _Cont,
	typename _Tx,
	typename... _Args>
	_Cont<_Tx, _Args...> operator | (const _Cont<_Tx, _Args...>& v, std::function<bool(_Tx)> f)
{
	_Cont<_Tx, _Args...> result;
	for (const auto e : v)
		if (f(e))
			result.push_back(e);
	return result;
}

/**
 * @brief reduce
 */
template <
	template <typename, typename...> class _Cont,
	typename _Tx,
	typename _R,
	typename... _Args>
	_R operator | (const _Cont<_Tx, _Args...>& v, std::function<_R(_R, _Tx)> f)
{
	return std::accumulate(v.begin(), v.end(), 0, f);
}

template <
	class LHS,
	class RHS,
	class = std::void_t<decltype(std::declval<RHS>()(std::declval<LHS>()))>>
	constexpr auto operator|(LHS&& lhs, RHS&& rhs) noexcept {
	return std::forward<RHS>(rhs)(std::forward<LHS>(lhs));
}

_STD_END

#endif /* _HULU_BASE_PIPE_RANGE_H_ */