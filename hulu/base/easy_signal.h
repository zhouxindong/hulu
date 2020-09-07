#pragma once
#ifndef _HULU_BASE_EASY_SIGNAL_H_
#define _HULU_BASE_EASY_SIGNAL_H_

#include "../gvals.h"

#include <functional>
#include <vector>
#include <type_traits>
#include <algorithm>

_HULU_BEGIN

template <int I>
struct placeholder {
	static constexpr int value = I;
};

_HULU_END

namespace std {
	template <int I>
	struct is_placeholder<hulu::placeholder<I>> :
		std::integral_constant<int, I> {};
}

_HULU_BEGIN

namespace detail
{
	template <std::size_t... Indices>
	struct indices {};

	//template <class Tuple, std::size_t... Indices>
	//std::array<int, std::tuple_size<Tuple>::value> 
	//	f_them_all(Tuple&& t, indices<Indices...>) 
	//{
	//	return std::array<int, std::tuple_size<Tuple>::value> 
	//	{ { f(std::get<Indices>(std::forward<Tuple>(t)))... } };
	//}

	template <std::size_t... Is>
	struct build_indices;

	template <std::size_t N, std::size_t... Is>
	struct build_indices<N, Is...>
		: build_indices<N - 1, N - 1, Is...> {};

	template <std::size_t... Is>
	struct build_indices<0, Is...> : indices<Is...> {};

	/**
	 * @brief need C++17
	 */
	 //template <std::size_t... Is>
	 //void show(indices<Is...>)
	 //{
	 //	(((std::cout << " ") << Is), ...);
	 //}

	template <std::size_t... Is>
	std::vector<std::size_t> make_index_vector(std::index_sequence<Is...>)
	{
		return { Is... };
	}

	template <std::size_t... Is>
	std::vector<std::size_t> make_index_vector(indices<Is...>)
	{
		return { Is... };
	}

	template <std::size_t... Is>
	auto gen_placeholders(indices<Is...>)
	{
		//return { placeholder<Is + 1>{}... };
		return std::make_tuple(placeholder<Is + 1>()...);
	}

	//template <typename Tuple>
	//using IndicesFor = build_indices<std::tuple_size<std::decay_t<Tuple>>::value>;

	//template <typename Tuple>
	//std::array<int, std::tuple_size<Tuple>::value> 
	//	f_them_all(Tuple&& t) 
	//{
	//	return f_them_all(std::forward<Tuple>(t), IndicesFor<Tuple> {});
	//}

	template<std::size_t... Is, class F, class... Args>
	auto easy_bind(indices<Is...>, F const& f, Args&&... args)
		-> decltype(std::bind(f, std::forward<Args>(args)...,
			placeholder<Is + 1>{}...))
	{
		return std::bind(f, std::forward<Args>(args)...,
			placeholder<Is + 1>{}...);
	}

	template<std::size_t... Is, class R, class C, class... Args>
	auto easy_bind(indices<Is...>, R(C::* pmf)(Args&&... args), C& obj)
	{
		return std::bind(pmf, obj, placeholder<Is + 1>{}...);
	}
} // detail::



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
	template <typename _Ret2, typename _Class, std::size_t... Is>
	void connect(_Ret2 _Class::* pmf, _Class& obj, detail::indices<Is...>)
	{
		slots_.push_back(std::bind(pmf, obj, /*std::placeholders::_1)*//*hulu::placeholder<1>{})*/
			placeholder<Is + 1>{}...));
	}

	template <typename _Ret2, typename _Class>
	void connect(_Ret2 _Class::* pmf, _Class& obj)
	{
		connect(pmf, obj, detail::build_indices<sizeof...(_Args)>{});
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
		std::for_each(slots_.cbegin(), slots_.cend(), [&](const auto& f) {
			f(std::forward<_Args>(args)...);
		});
	}

private:
	std::vector<std::function<_Ret(_Args...)>> slots_;
	std::vector<std::reference_wrapper<Easy_signal>> signals_;
};

_HULU_END

#endif /* _HULU_BASE_EASY_SIGNAL_H_ */