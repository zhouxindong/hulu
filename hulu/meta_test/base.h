#pragma once
#ifndef _HULU_METAPROG_BASE_H_
#define _HULU_METAPROG_BASE_H_

#include "../gvals.h"

_HULU_BEGIN

/**
 * @brief Print get value information at compile time
 */
template <typename T>
struct Print
{
	//operator char()
	//{
	//	return Value + 0xFF; // invoke overflow warn log!
	//}
	const int Value = 1 / (sizeof(T) - sizeof(T));
};

template <typename T>
struct CompileError;

#define __DO_JOIN(symbol1, symbol2) symbol1##symbol2
#define  _JOIN(symbol1, symbol2) __DO_JOIN(symbol1, symbol2)
#define HULU_UNIQUE_NAME(prefix) _JOIN(prefix, __LINE__)

//#define __print(...) char HULU_UNIQUE_NAME(print_value_) = Print<__VA_ARGS__>()
#define __print(...) Print<__VA_ARGS__> HULU_UNIQUE_NAME(print_debug_)

/**
 * @brief add pointer for T
 */
template <typename T>
struct PointerOf
{
	using Result = T*;
};

/**
 * ���ּ�ʹ��Ԫ�����ķ�ʽ
 1. ͨ���궨�����ƺ������õ����ͻ�ȡ��ʽ
 2. ͨ�����������ͱ���
 */
#define __pointer(...) typename PointerOf<__VA_ARGS__>::Result

template <typename T>
using pointer_of_t = typename PointerOf<T>::Result;

template <typename T>
struct Pointer2Of
{
	using Result = __pointer(__pointer(T));
};

template <typename T>
using pointer_2_of_t = typename Pointer2Of<T>::Result;

/**
 * @brief high order meta function
 * @param T is used for template template argument class Function
 */
template <int N, typename T, template <typename> class Function>
struct Times
{
	using Result = typename Function<
		typename Times<N - 1, T, Function>::Result>::Result;
};

template <typename T, template <typename> class Function>
struct Times<1, T, Function>
{
	using Result = typename Function<T>::Result;
};

template <int N, typename T, template <typename> class Function>
using Times_t = typename Times<N, T, Function>::Result;

/**
 * ��������ģ������ͷ���ֵ���ͻ���ͳһԪ�����Ĳ����ͷ���ֵȡ�÷�ʽ
 */

/**
 * @brief IntType
 */
template <int V>
struct IntType
{
	enum { Value = V };
	using Result = IntType<V>;
};

#define __int(value) typename IntType<value>::Result

template <int V>
constexpr int int_type_v = IntType<V>::Value;

/**
 * @brief BoolType
 */
template <bool V>
struct BoolType;

template <>
struct BoolType<true>
{
	enum { Value = true };
	using Result = BoolType<true>;
};

template <>
struct BoolType<false>
{
	enum { Value = false };
	using Result = BoolType<false>;
};

using TrueType = BoolType<true>;
using FalseType = BoolType<false>;

#define __bool(...) typename BoolType<__VA_ARGS__>::Result
#define __true() typename TrueType::Result
#define __false() typename FalseType::Result

/**
 * @brief EmptyType
 */
struct EmptyType
{
};

#define __empty() EmptyType

/**
 * @brief IfThenElse
 */
template <typename Condition, typename Then, typename Else>
struct IfThenElse;

template <typename Then, typename Else>
struct IfThenElse<TrueType, Then, Else>
{
	using Result = Then;
};

template <typename Then, typename Else>
struct IfThenElse<FalseType, Then, Else>
{
	using Result = Else;
};

#define __if(...) typename IfThenElse<__VA_ARGS__>::Result

template <typename T, typename U>
using LargerType = __if(/*__bool(sizeof(T) > sizeof(U))*/
	BoolType<(sizeof(T)>sizeof(U))>, T, U);

/**
 * @breif IsConvertible
 */
template <typename T, typename U>
struct IsConvertible
{
private:
	using Yes = char;
	struct No { char dummy[2]; };

	static Yes test(U);
	static No test(...);
	static T self();

public:
	using Result = BoolType<sizeof(test(self())) == sizeof(Yes)>;
};

#define __is_convertible(...) typename IsConvertible<__VA_ARGS__>::Result
#define __is_both_convertible(T, U) __and(__is_convertible(T,U), __is_convertible(U,T))

#define __is_base_of(T, U)		\
__and(__is_convertible(const U*, const T*)		\
__and(__not(__is_eq(const T*, const void*)),	\
__not(__is_eq(const T, const U))))

template <typename T, typename U>
constexpr bool is_convertible_v = IsConvertible<T, U>::Result::Value;

/**
 * @brief ASSERT_TRUE
 */
#define ASSERT_TRUE(...) static_assert(Value<__VA_ARGS__>::Result, "Assert Failed: expect be true, but be false!")
#define ASSERT_FALSE(...) static_assert(!Value<__VA_ARGS__>::Result, "Assert Failed: expect be false, but be true!")

#define ASSERT_EQ(/*T, Expected*/...) static_assert(Value<typename IsEqual</*T, Expected*/__VA_ARGS__>::Result>::Result, "Assert Failed: expect be true, but be false!")
#define ASSERT_NE(/*T, Expected*/...) static_assert(!Value<typename IsEqual</*T, Expected*/__VA_ARGS__>::Result>::Result, "Assert Failed: expect be false, but be true!");

//#define ASSERT_FALSE(T)
//static_assert(!__value(T), "Assert Failed: expect '#T' be false, but be true!")

/**
 * @brief NullType
 */
struct NullType;

#define __hulu_null() NullType

/**
 * @breif Valid
 */
template <typename T>
struct Valid
{
	using Result = __true();
};

template <>
struct Valid<NullType>
{
	using Result = __false();
};

#define __hulu_valid(...) typename Valid<__VA_ARGS__>::Result

#define ASSERT_VALID(T) static_assert(Value<typename Valid<T>::Result>::Result, "Assert Failed: expect be valid, but be invalid!")
#define ASSERT_INVALID(T) static_assert(!Value<typename Valid<T>::Result>::Result, "Assert Failed: expect be invalid, but be valid!")

/**
 * @brief TestCase
 ��ν������������ʵ�������Ͷ��壬������������Ե�Ԫ��������(��ģ��)
 ����ͨ��������ͨ��
 */
#define TEST(name) struct HULU_UNIQUE_NAME(meta_test_)

/**
 * @brief Fixture
 ��ν�����׼����ڶԲ����������飬ͬһ�׼��ڵ����������������
 */
#define FIXTURE(name) namespace meta_fixture_##name


_HULU_END

#endif /* _HULU_METAPROG_BASE_H_ */