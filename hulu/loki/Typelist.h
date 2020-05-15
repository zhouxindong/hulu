#pragma once
#ifndef _HULU_LOKI_TYPELIST_H_
#define _HULU_LOKI_TYPELIST_H_

#include "../gvals.h"
#include "NullType.h"
#include <limits>

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
    //static constexpr int value = 1 + Typelist_index_of<Typelist<Tail...>, T>::value;
private:
    static constexpr int temp = Typelist_index_of<Typelist<Tail...>, T>::value; // 
public:
    static const int value = temp == -1 ? -1 : 1 + temp;
};

template <typename T>
struct Typelist_index_of<Typelist<>, T>
{
    //static constexpr int value = -100000000;
    static constexpr int value = -1;
};

template <typename List, typename T>
constexpr int Typelist_index_of_v = Typelist_index_of<List, T>::value < 0 ? -1 : Typelist_index_of<List, T>::value;

/**
 * Append
 */


_HULU_END

#endif /* _HULU_LOKI_TYPELIST_H_ */