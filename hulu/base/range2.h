#pragma once
#ifndef _HULU_BASE_RANGE2_H_
#define _HULU_BASE_RANGE2_H_

#include "../gvals.h"

#include <type_traits>
#include <vector>

_HULU_BEGIN

/**
 * @brief Convenience notation for chaining ranges.
 * @note this enables `operator|` for any pair where RHS is callable with LHS as its only
    argument. Therefore, it may be best to selectively import this operator into your scope with
    `using`. If it simply cannot be imported without clashing with other definitions of `operator|`,
    you can use the alternative chaining syntax using `operator()`: `rhs(lhs)`.
 */
template <
	class LHS,
	class RHS,
	class = std::void_t<decltype(std::declval<RHS>()(std::declval<LHS>()))>>
	constexpr auto operator|(LHS&& lhs, RHS&& rhs) noexcept {
	return std::forward<RHS>(rhs)(std::forward<LHS>(lhs));
}

//namespace detail {
//	// This exists only to maintain some sanity in figuring out overload resolution for
//	// as_input_range().
//	struct input_category {
//		struct input_range {};
//		struct sink {};
//		struct other {};
//	};
//
//	template <class, class Enable = void>
//	struct input_category_of {
//		using type = input_category::other;
//	};
//	template <class Sink>
//	struct input_category_of<Sink, std::enable_if_t<is_input_range_v<Sink>>> {
//		using type = input_category::input_range;
//	};
//	template <class Sink>
//	struct input_category_of<Sink, std::enable_if_t<is_sink_v<Sink>>> {
//		using type = input_category::sink;
//	};
//
//	template <class Sink>
//	using input_category_of_t = typename input_category_of<remove_cvref_t<Sink>>::type;
//
//	template <class Sink>
//	constexpr decltype(auto) as_input_range_impl(input_category::input_range, Sink&& range) noexcept {
//		return std::forward<Sink>(range);
//	}
//
//	template <class Sink>
//	constexpr auto as_input_range_impl(input_category::sink, Sink&& input) noexcept {
//		static_assert(
//			!std::is_lvalue_reference_v<Sink>,
//			"Please only convert sinks to input ranges with rvalue references (for efficiency).");
//		using RX_NAMESPACE::sink;
//		// Store the output in a temporary vector.
//		using output_type = remove_cvref_t<typename remove_cvref_t<Sink>::output_type>;
//		std::vector<output_type> vec;
//		sink(std::move(input), vec);
//		return vector_range<output_type>{std::move(vec)};
//	}
//
//	template <class Sink>
//	constexpr auto as_input_range_impl(input_category::other, const Sink& container) noexcept {
//		return iterator_range(container.begin(), container.end());
//	}
//
//	template <class Sink, size_t N>
//	constexpr auto as_input_range_impl(input_category::other, Sink(&arr)[N]) noexcept {
//		return iterator_range(std::begin(arr), std::end(arr));
//	}
//} // namespace detail

template <class R>
constexpr decltype(auto) as_input_range(R&& range) {
	using category = detail::input_category_of_t<R>;
	return detail::as_input_range_impl(category{}, std::forward<R>(range));
}
_HULU_END

#endif /* _HULU_BASE_RANGE2_H_ */