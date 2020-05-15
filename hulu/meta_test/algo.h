#pragma once
#ifndef _HULU_METAPROG_ALOG_H_
#define _HULU_METAPROG_ALOG_H_

#include "../gvals.h"
#include "base.h"

_HULU_BEGIN

/**
 * @brief IsEqual
 */
template <typename T, typename U>
struct IsEqual
{
	using Result = FalseType;
};

template <typename T>
struct IsEqual<T, T>
{
	using Result = TrueType;
};

#define __is_eq(...) typename IsEqual<__VA_ARGS__>::Result

/**
 * @brief Value
 */
template <typename T>
struct Value
{
	enum { Result = T::Value };
};

template <>
struct Value<EmptyType>
{
	enum { Result = 0 };
};

#define __value(...) Value<__VA_ARGS__>::Result

/**
 * @brief Add
 */
template <typename T1, typename T2>
struct Add;

template <int V1, int V2>
struct Add<IntType<V1>, IntType<V2>>
{
    using Result = IntType<V1 + V2>;
};

#define __add(...) typename Add<__VA_ARGS__>::Result

/**
 * @breif Inc
 */
template <typename T>
struct Inc;

template <int V>
struct Inc<IntType<V>>
{
    using Result = IntType<V + 1>;
};

#define __inc(...) typename Inc<__VA_ARGS__>::Result

/**
 * @brief Dec
 */
template <typename T>
struct Dec;

template <int V>
struct Dec<IntType<V>>
{
    using Result = IntType<V - 1>;
};

#define __dec(...) typename Dec<__VA_ARGS__>::Result

/**
 * @brief Sub
 */
template <typename T1, typename T2>
struct Sub;

template <int V1, int V2>
struct Sub<IntType<V1>, IntType<V2>>
{
    using Result = IntType<V1 - V2>;
};

#define __sub(...) typename Sub<__VA_ARGS__>::Result

/**
 * @brief Mul
 */
template <typename T1, typename T2>
struct Mul;

template <int V1, int V2>
struct Mul<IntType<V1>, IntType<V2>>
{
    using Result = IntType<V1 * V2>;
};

#define __mul(...) typename Mul<__VA_ARGS__>::Result

/**
 * @breif Div
 */
template <typename T1, typename T2>
struct Div;

template <int V1, int V2>
struct Div<IntType<V1>, IntType<V2>>
{
    using Result = IntType<V1 / V2>;
};

#define __div(...) typename Div<__VA_ARGS__>::Result

/**
 * @breif
 */
template <typename T1, typename T2>
struct Mod;

template <int V1, int V2>
struct Mod<IntType<V1>, IntType<V2>>
{
    using Result = IntType<V1% V2>;
};

#define __mod(...) typename Mod<__VA_ARGS__>::Result

/**
 * @breif Not
 */
template <typename T>
struct Not;

template <bool V>
struct Not<BoolType<V>>
{
    using Result = BoolType<!V>;
};

#define __not(...) typename Not<__VA_ARGS__>::Result

/**
 * @breif And
 */
template <typename T1, typename T2>
struct And;

template <bool V1, bool V2>
struct And<BoolType<V1>, BoolType<V2>>
{
    using Result = BoolType<V1&& V2>;
};

#define __and(...) typename And<__VA_ARGS__>::Result

/**
 * @breif Or
 */
template <typename T1, typename T2>
struct Or;

template <bool V1, bool V2>
struct Or<BoolType<V1>, BoolType<V2>>
{
    using Result = BoolType<V1 || V2>;
};

#define __or(...) typename Or<__VA_ARGS__>::Result

/**
 * @brief Sum
 */
template <typename ...Numbers> 
struct Sum;

template <typename Number, typename ...LeftNumbers>
struct Sum<Number, LeftNumbers...>
{
    using Result = typename Add<Number, typename Sum<LeftNumbers...>::Result>::Result;
};

template <>
struct Sum<>
{
    using Result = IntType<0>;
};

#define __sum(...) typename Sum<__VA_ARGS__>::Result

_HULU_END

#endif /* _HULU_METAPROG_ALOG_H_ */