#pragma once
#ifndef _HULU_STLX_CASE_INSENSIVE_CHAR_TRAITS_H_
#define _HULU_STLX_CASE_INSENSIVE_CHAR_TRAITS_H_

/**
 * 
typedef basic_string<char, char_traits<char>, allocator<char> >
string;
 */

#include "../gvals.h"
#include <iosfwd>
#include <string>

_HULU_BEGIN

/**
 * @brief modify special member to case insensive
 * @note derived from char_traits<char> so you can only defined something to modified
 */
struct Case_insensive_char_traits : public std::char_traits<char>
{
	/**
	 * @brief operator ==
	 */
	static bool eq(char c1, char c2)
	{
		return _CSTD toupper(c1) == _CSTD toupper(c2);
	}

	/**
	 * @brief operator <
	 */
	static bool lt(char c1, char c2)
	{
		return _CSTD toupper(c1) < _CSTD toupper(c2);
	}

	/**
	 * @brief two char string compare
	 */
	static int compare(const char* s1, const char* s2, size_t n)
	{
		return _CSTD _memicmp(s1, s2, n);
	}

	static const char* find(const char* s, int n, char a)
	{
		while (n-- > 0 && _CSTD toupper(*s) != _CSTD toupper(a))
		{
			++s;
		}
		return n >= 0 ? s : 0;
	}
};

typedef std::basic_string<char, Case_insensive_char_traits> Case_insensive_string;

_HULU_END

#endif // _HULU_STLX_CASE_INSENSIVE_CHAR_TRAITS_H_