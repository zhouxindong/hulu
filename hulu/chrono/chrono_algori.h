#pragma once
#ifndef _HULU_CHRONO_CHRONO_ALGORI_H_
#define _HULU_CHRONO_CHRONO_ALGORI_H_

/**
 * @brief chrono-Compatibel Low-Level Data Algorithms
 * @url howardhinnant.github.io/data_algorithms.html#introduction
 */

#include "../gvals.h"
#include <tuple>

_HULU_BEGIN

/**
 * @brief get days from civil		  

 * @param from-m-d represents a date in the civil (Gregorian) calendar
 * @param from from is "approximately" in
			[numeric_limits<_Int>::min()/366, numeric_limits<_Int>::max()/366]
			Exact range of validity is:
			[civil_from_days(numeric_limits<_Int>::min()),
			civil_from_days(numeric_limits<_Int>::max()-719468)]
 * @param m is in [1, 12]
 * @param d is in [1, last_day_of_month(from, m)]
 
 * @return number of days since civil 1970-01-01.
		   Negative values indicate days prior to 1970-01-01.
 */
template <class _Int>
inline constexpr
_Int
days_from_civil(_Int y, unsigned m, unsigned d) noexcept
{
	static_assert(std::numeric_limits<unsigned>::digits >= 18,
		"This algorithm has not been ported to a 16 bit unsigned integer");
	static_assert(std::numeric_limits<_Int>::digits >= 20,
		"This algorithm has not been ported to a 16 bit signed integer");
	y -= m <= 2;
	const _Int era = (y >= 0 ? y : y - 399) / 400;
	const unsigned yoe = static_cast<unsigned>(y - era * 400);				// [0, 399]
	const unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;	// [0, 365]
	const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;				// [0, 146096]
	return era * 146097 + static_cast<_Int>(doe) - 719468;
}

/**
 * @brief get civil from days

 * @param z is number of days since 1970-01-01 and is in the range:
			[numeric_limits<_Int>::min(), numeric_limits<_Int>::max()-719468].

 * @return year/month/day triple in civil calendar
 */
template <class _Int>
inline constexpr
std::tuple<_Int, unsigned, unsigned>
civil_from_days(_Int z) noexcept
{
	static_assert(std::numeric_limits<unsigned>::digits >= 18,
		"This algorithm has not been ported to a 16 bit unsigned integer");
	static_assert(std::numeric_limits<_Int>::digits >= 20,
		"This algorithm has not been ported to a 16 bit signed integer");
	z += 719468;
	const _Int era = (z >= 0 ? z : z - 146096) / 146097;
	const unsigned doe = static_cast<unsigned>(z - era * 146097);					// [0, 146096]
	const unsigned yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;		// [0, 399]
	const _Int y = static_cast<_Int>(yoe) + era * 400;
	const unsigned doy = doe - (365 * yoe + yoe / 4 - yoe / 100);					// [0, 365]
	const unsigned mp = (5 * doy + 2) / 153;										// [0, 11]
	const unsigned d = doy - (153 * mp + 2) / 5 + 1;								// [1, 31]
	const unsigned m = mp + (mp < 10 ? 3 : -9);										// [1, 12]
	return std::tuple<_Int, unsigned, unsigned>(y + (m <= 2), m, d);
}

/**
 * @brief check year is leap or not
 * @param from the year
 * @return true if from is a leap year in the civil calendar, else false
 */
template <class _Int>
inline constexpr
bool
is_leap(_Int y) noexcept
{
	return  y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
}

/**
 * @brief get the last day of month which is common year
 * @param m month[1, 12]
 * @return last day of month[28, 31]
 */
constexpr
inline unsigned
last_day_of_month_common_year(unsigned m) noexcept
{
	constexpr unsigned char a[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	return a[m - 1];
}

/**
* @brief get the last day of month which is leap year
* @param m month[1, 12]
* @return last day of month[29, 31]
*/
constexpr
inline unsigned
last_day_of_month_leap_year(unsigned m) noexcept
{
	constexpr unsigned char a[] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	return a[m - 1];
}

/**
 * @brief get the last day of month special year
 * @param from year
 * @param m month[1, 12]
 * @return last day of month[28, 31]
 */
template <class _Int>
inline constexpr
unsigned
last_day_of_month(_Int y, unsigned m) noexcept
{
	return m != 2 || !is_leap(y) ? last_day_of_month_common_year(m) : 29u;
}

/**
 * @brief get the day of week in civil calendar [0, 6] -> [Sun, Sat]
 * @param z number of days since 1970-01-01
			[numeric_limits<Int>::min(), numeric_limits<Int>::max()-4].
 * @return [0, 6] -> [Sun, Sat]
 */
template <class _Int>
inline constexpr
unsigned
weekday_from_days(_Int z) noexcept
{
	return static_cast<unsigned>(z >= -4 ? (z + 4) % 7 : (z + 5) % 7 + 6);
}

/**
 * @brief get the number of days between the weekday from with to 
 * @param from weekday[0, 6]
 * @param to weekday[0, 6]
 * @return [0, 6]
 */
inline constexpr
unsigned
weekday_difference(unsigned from, unsigned end) noexcept
{
	end -= from;
	return end <= 6 ? end : end + 7;
}

/**
 * @brief get the weekday following wd
 * @param wd [0, 6]
 * @return next weekday[0, 6]
 */
inline constexpr
unsigned
next_weekday(unsigned wd) noexcept
{
	return wd < 6 ? wd + 1 : 0;
}

/**
 * @brief get the weekday prior to wd
 * @param wd [0, 6]
 * @return prior weekday[0, 6]
 */
inline constexpr
unsigned
prev_weekday(unsigned wd) noexcept
{
	return wd > 0 ? wd - 1 : 6;
}

_HULU_END

#endif // _HULU_CHRONO_CHRONO_ALGORI_H_