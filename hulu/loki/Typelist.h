#pragma once
#ifndef _HULU_LOKI_TYPELIST_H_
#define _HULU_LOKI_TYPELIST_H_

#include "../gvals.h"
#include "NullType.h"
#include <type_traits>

_HULU_BEGIN

template <typename ...Elements>
struct Typelist
{
};

/**
 * Length
 */
template <typename List>
struct Typelist_length;

template <typename Head, typename ...Tail>
struct Typelist_length <Typelist<Head, Tail...>>
{
    static constexpr int value = 1 + Typelist_length<Typelist<Tail...>>::value;
};

template <>
struct Typelist_length<Typelist<>>
{
    static constexpr int value = 0;
};

template <typename List>
constexpr int Typelist_length_v = Typelist_length<List>::value;

/**
 * indexer[]
 */
template <typename List, unsigned int Index>
struct Typelist_at
{
    using type = NullType;
};

template <typename Head, typename ...Tail, unsigned int Index>
struct Typelist_at<Typelist<Head, Tail...>, Index>
{
    using type = typename Typelist_at<Typelist<Tail...>, Index - 1>::type;
};

template <typename Head, typename ...Tail>
struct Typelist_at<Typelist<Head, Tail...>, 0>
{
    using type = Head;
};

template <typename List, unsigned int Index>
using Typelist_at_t = typename Typelist_at<List, Index>::type;

/**
 * IndexOf
 */
template <typename List, typename T>
struct Typelist_index_of;

template <typename T, typename ...Tail>
struct Typelist_index_of<Typelist<T, Tail...>, T>
{
    static constexpr int value = 0;
};

template <typename Head, typename ...Tail, class T>
struct Typelist_index_of<Typelist<Head, Tail...>, T>
{
private:
    static constexpr int temp = Typelist_index_of<Typelist<Tail...>, T>::value; // 
public:
    static const int value = temp == -1 ? -1 : 1 + temp;
};

template <typename T>
struct Typelist_index_of<Typelist<>, T>
{
    static constexpr int value = -1;
};

template <typename List, typename T>
constexpr int Typelist_index_of_v = Typelist_index_of<List, T>::value < 0 ? -1 : Typelist_index_of<List, T>::value;

/**
 * Append
 */
template <typename List, typename T>
struct Typelist_append;

template <typename ...Elements, typename T>
struct Typelist_append<Typelist<Elements...>, T>
{
    using type = Typelist<Elements..., T>;
};

template <typename ...Elements1, typename ...Elements2>
struct Typelist_append<Typelist<Elements1...>, Typelist<Elements2...>>
{
    using type = Typelist<Elements1..., Elements2...>;
};

template <typename List, typename T>
using Typelist_append_t = typename Typelist_append<List, T>::type;

/**
 * Erase
 */
template <typename List, typename T>
struct Typelist_erase;

template <typename T, typename ...Tail>
struct Typelist_erase<Typelist<T, Tail...>, T>
{
    using type = Typelist<Tail...>;
};

template <typename Head, typename ...Tail, typename T>
struct Typelist_erase<Typelist<Head, Tail...>, T>
{
    using type = Typelist_append_t<Typelist<Head>, typename Typelist_erase<Typelist<Tail...>, T>::type>;
};

template <typename T>
struct Typelist_erase<Typelist<>, T>
{
    using type = Typelist<>;
};

template <typename List, typename T>
using Typelist_erase_t = typename Typelist_erase<List, T>::type;

/**
 * EraseAll
 */
template <typename List, typename T>
struct Typelist_erase_all;

template <typename T>
struct Typelist_erase_all<Typelist<>, T>
{
    using type = Typelist<>;
};

template <typename T, typename ...Tail>
struct Typelist_erase_all<Typelist<T, Tail...>, T>
{
    using type = typename Typelist_erase_all<Typelist<Tail...>, T>::type;
};

template <typename Head, typename ...Tail, typename T>
struct Typelist_erase_all<Typelist<Head, Tail...>, T>
{
    using type = Typelist_append_t<Typelist<Head>, typename Typelist_erase_all<Typelist<Tail...>, T>::type>;
};

template <typename List, typename T>
using Typelist_erase_all_t = typename Typelist_erase_all<List, T>::type;

/**
 * Unique
 */
template <typename List>
struct Typelist_unique;

template <>
struct Typelist_unique<Typelist<>>
{
    using type = Typelist<>;
};

template <typename Head, typename ...Tail>
struct Typelist_unique<Typelist<Head, Tail...>>
{
private:
    using l1 = typename Typelist_unique<Typelist<Tail...>>::type;
    using l2 = Typelist_erase_t<l1, Head>;

public:
    using type = Typelist_append_t<Typelist<Head>, l2>;
};

template <typename List>
using Typelist_unique_t = typename Typelist_unique<List>::type;

/**
 * Replace
 */
template <typename List, typename From, typename To>
struct Typelist_replace;

template <typename From, typename To>
struct Typelist_replace<Typelist<>, From, To>
{
    using type = Typelist<>;
};

template <typename From, typename ...Tail, typename To>
struct Typelist_replace<Typelist<From, Tail...>, From, To>
{
    using type = Typelist<To, Tail...>;
};

template <typename Head, typename ...Tail, typename From, typename To>
struct Typelist_replace<Typelist<Head, Tail...>, From, To>
{
    using type = Typelist_append_t<Typelist<Head>, 
        typename Typelist_replace<Typelist<Tail...>, From, To>::type>;
};

template <typename List, typename From, typename To>
using Typelist_replace_t = typename Typelist_replace<List, From, To>::type;

/**
 * ReplaceAll
 */
template <typename List, typename From, typename To>
struct Typelist_replace_all;

template <typename From, typename To>
struct Typelist_replace_all<Typelist<>, From, To>
{
    using type = Typelist<>;
};

template <typename From, typename ...Tail, typename To>
struct Typelist_replace_all<Typelist<From, Tail...>, From, To>
{
    using type = Typelist_append_t<Typelist<To>,
        typename Typelist_replace_all<Typelist<Tail...>, From, To>::type>;
};

template <typename Head, typename ...Tail, typename From, typename To>
struct Typelist_replace_all<Typelist<Head, Tail...>, From, To>
{
    using type = Typelist_append_t<Typelist<Head>, 
        typename Typelist_replace_all<Typelist<Tail...>, From, To>::type>;
};

template <typename List, typename From, typename To>
using Typelist_replace_all_t = typename Typelist_replace_all<List, From, To>::type;

/**
 * Front
 */
template <typename List>
struct Typelist_front;

template <typename Head, typename ...Tail>
struct Typelist_front<Typelist<Head, Tail...>>
{
    using type = Head;
};

template <>
struct Typelist_front<Typelist<>>
{
    using type = NullType;
};

template <typename List>
using Typelist_front_t = typename Typelist_front<List>::type;

/**
 * PopFront
 */
template <typename List>
struct Typelist_pop_front;

template <typename Head, typename ...Tail>
struct Typelist_pop_front<Typelist<Head, Tail...>>
{
    using type = Typelist<Tail...>;
};

template <>
struct Typelist_pop_front<Typelist<>>
{
    using type = Typelist<>;
};

template <typename List>
using Typelist_pop_front_t = typename Typelist_pop_front<List>::type;

/**
 * Prepends
 */
template <typename List, typename T>
struct Typelist_prepend;

template <typename ...Elements, typename T>
struct Typelist_prepend<Typelist<Elements...>, T>
{
    using type = Typelist<T, Elements...>;
};

template <typename List, typename T>
using Typelist_prepend_t = typename Typelist_prepend<List, T>::type;

/**
 * LargestType
 */
template <typename List>
struct Typelist_largest_type;

template <typename Head, typename ...Tail>
struct Typelist_largest_type<Typelist<Head, Tail...>>
{
private:
    using Rest = typename Typelist_largest_type<Typelist<Tail...>>::type;

public:
    using type = std::conditional_t<
        (sizeof(Head) >= sizeof(Rest)),
        Head,
        Rest
    >;
};

template <>
struct Typelist_largest_type<Typelist<>>
{
    using type = char;
};

template <typename List>
using Typelist_largest_type_t = typename Typelist_largest_type<List>::type;

/**
 * IsEmpty
 */
template <typename List>
struct Typelist_is_empty
{
    static constexpr bool value = false;
};

template <>
struct Typelist_is_empty<Typelist<>>
{
    static constexpr bool value = true;
};

template <typename List>
constexpr bool Typelist_is_empty_v = Typelist_is_empty<List>::value;

/**
 * Reverse
 */
template <typename List>
struct Typelist_reverse;

template <typename Head, typename ...Tail>
struct Typelist_reverse<Typelist<Head, Tail...>>
{
private:
    using temp = typename Typelist_reverse<Typelist<Tail...>>::type;
public:
    using type = Typelist_append_t<temp, Typelist<Head>>;
};

template <typename T>
struct Typelist_reverse<Typelist<T>>
{
    using type = Typelist<T>;
};

template <>
struct Typelist_reverse<Typelist<>>
{
    using type = Typelist<>;
};

template <typename List>
using Typelist_reverse_t = typename Typelist_reverse<List>::type;

/**
 * PopBack
 */
template <typename List>
struct Typelist_pop_back
{
    using type = Typelist_reverse_t<Typelist_pop_front_t<Typelist_reverse_t<List>>>;
};

template <typename List>
using Typelist_pop_back_t = typename Typelist_pop_back<List>::type;

/**
 * MostDerived
 */
template <typename List, typename Base>
struct Typelist_most_derived;

template <typename Base>
struct Typelist_most_derived<Typelist<>, Base>
{
    using type = Base;
};

template <typename Head, typename ...Tail, typename Base>
struct Typelist_most_derived<Typelist<Head, Tail...>, Base>
{
private:
    using candidate = typename Typelist_most_derived<Typelist<Tail...>, Base>::type;

public:
    using type = std::conditional_t<
        std::is_base_of_v<candidate, Head>,
        Head,
        candidate
    >;
};

template <typename List, typename Base>
using Typelist_most_derived_t = typename Typelist_most_derived<List, Base>::type;

/**
 * DerivedToFront
 */
template <typename List>
struct Typelist_derived_to_front;

template <>
struct Typelist_derived_to_front<Typelist<>>
{
    using type = Typelist<>;
};

template <typename Head, typename ...Tail>
struct Typelist_derived_to_front<Typelist<Head, Tail...>>
{
private:
    using temp = Typelist_most_derived_t<Typelist<Tail...>, Head>;
    using rl = Typelist_replace_t<Typelist<Tail...>, temp, Head>;
    using l = typename Typelist_derived_to_front<rl>::type;

public:
    using type = Typelist_append_t<Typelist<temp>, l>;
};

template <typename List>
using Typelist_derived_to_front_t = typename Typelist_derived_to_front<List>::type;

/**
 * 
 */

_HULU_END

#endif /* _HULU_LOKI_TYPELIST_H_ */