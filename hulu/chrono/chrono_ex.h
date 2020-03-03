#pragma once
#ifndef _HULU_CHRONO_CHRONO_EX_H_
#define _HULU_CHRONO_CHRONO_EX_H_

#include "../gvals.h"

#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>

#include "chrono_algori.h"

_HULU_BEGIN

typedef std::chrono::duration<
	int, std::ratio_multiply<
	std::chrono::hours::period, std::ratio<24>>> Days;

/**
 * @brief get local time zone
 * @return time zone in minutes, example for Beijing is -480
 */
inline
long
time_zone() noexcept
{
	TIME_ZONE_INFORMATION tzi;
	GetTimeZoneInformation(&tzi);
	return tzi.Bias;
}

/**
 * @brief get the UTC time of local time
 * @param 
			tp local time
 * @return UTC time
 */
constexpr
inline
std::chrono::system_clock::time_point
to_utc(std::chrono::system_clock::time_point const& tp) noexcept
{
	return tp + std::chrono::minutes(time_zone());
}

/**
 * @brief get the local time of UTC time
 * @param
			tp UTC time
 * @return local time
 */
constexpr
inline
std::chrono::system_clock::time_point
to_local(std::chrono::system_clock::time_point const& tp) noexcept
{
	return tp - std::chrono::minutes(time_zone());
}

/**
 * @brief get time_point by y-m-d-h-m-s-ms
 */
constexpr
inline
std::chrono::system_clock::time_point
to_time_point(
	unsigned year, unsigned mon, unsigned day,
	unsigned hour = 0, unsigned min = 0,
	unsigned sec = 0, unsigned ms = 0) noexcept
{
	return std::chrono::system_clock::time_point(
		Days(days_from_civil(year, mon, day)) +
		std::chrono::hours(hour) +
		std::chrono::minutes(min) +
		std::chrono::seconds(sec) +
		std::chrono::milliseconds(ms)
	);
}

/**
 * @brief get the days at 0000-01-01
 * @return -719528 because that -719468[1970-1-1 -> 0000-3-1]
 */
constexpr
inline
Days
proleptic_gregorian_epoch() noexcept
{
	return Days(days_from_civil(0, 1, 1));
}

/**
 * @brief parse time point to y/m/d/h/m/s/ms
 */
inline
std::tuple<unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned>
tokenize_time_point(std::chrono::system_clock::time_point const& tp) noexcept
{
	using namespace std;
	using namespace std::chrono;

	auto acc = tp.time_since_epoch();
	auto delta = acc - proleptic_gregorian_epoch();
	auto day = duration_cast<Days>(acc);
	if (acc.count() < 0 &&
		acc.count() % -864000000000 != 0) day -= Days(1); // -432000000000 duration_cast to 0!!

	unsigned y;
	unsigned m;
	unsigned d;
	tie(y, m, d) = civil_from_days(day.count());

	Days dt = duration_cast<Days>(delta);
	delta -= dt;
	auto hour = duration_cast<hours>(delta);
	delta -= hour;
	auto min = duration_cast<minutes>(delta);
	delta -= min;
	auto sec = duration_cast<seconds>(delta);
	delta -= sec;
	auto ms = duration_cast<milliseconds>(delta);

	return make_tuple(y, m, d, (unsigned)hour.count(), (unsigned)min.count(),
		(unsigned)sec.count(), (unsigned)ms.count());
}

/**
 * @brief format a time_point value to string
 */
inline
std::string
time_point_to_string(std::chrono::system_clock::time_point const& tp) noexcept
{
	auto tu = tokenize_time_point(tp);

	std::ostringstream stream;
	stream << std::get<0>(tu) << "-";
	stream << std::setw(2) << std::setfill('0') << std::get<1>(tu) << '-';
	stream << std::setw(2) << std::setfill('0') << std::get<2>(tu) << ' ';
	stream << std::setw(2) << std::setfill('0') << std::get<3>(tu) << ':';
	stream << std::setw(2) << std::setfill('0') << std::get<4>(tu) << ':';
	stream << std::setw(2) << std::setfill('0') << std::get<5>(tu) << '.';
	stream << std::setw(3) << std::setfill('0') << std::get<6>(tu);

	return stream.str();
}

/**
 * @brief cast time point to seconds
 */
constexpr
inline
long long
time_point_to_sec(std::chrono::system_clock::time_point const& tp) noexcept
{
	return std::chrono::duration_cast<std::chrono::seconds>
		(tp.time_since_epoch()).count();
}

/**
 * @brief cast time point to milliseconds
 */
constexpr
inline
long long
time_point_to_ms(std::chrono::system_clock::time_point const& tp) noexcept
{
	return std::chrono::duration_cast<std::chrono::milliseconds>
		(tp.time_since_epoch()).count();
}

/**
 * @brief cast seconds to time point
 */
constexpr
inline
std::chrono::system_clock::time_point
sec_to_time_point(long long sec) noexcept
{
	return std::chrono::system_clock::time_point(std::chrono::seconds(sec));
}

/**
 * @brief cast milliseconds to time point
 */
constexpr
inline
std::chrono::system_clock::time_point
ms_to_time_point(long long ms) noexcept
{
	return std::chrono::system_clock::time_point(std::chrono::milliseconds(ms));
}

/**
 * @brief calculate the elapse seconds now to the begin
 */
constexpr
inline
long long
elapse_sec(std::chrono::system_clock::time_point const& begin) noexcept
{
	return std::chrono::duration_cast<std::chrono::seconds>
		(std::chrono::system_clock::now() - begin).count();
}

/**
 * @brief calculate the elapse milliseconds now to the begin
 */
constexpr
inline
long long
elapse_ms(std::chrono::system_clock::time_point const& begin) noexcept
{
	return std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::system_clock::now() - begin).count();
}

_HULU_END

_STD_BEGIN

namespace chrono
{
	/**
	 * @brief operator << for chrono::system_clock::time_point
	 */
	inline
		ostream&
		operator << (ostream& out, chrono::system_clock::time_point const& tp) noexcept
	{
		using namespace hulu;
		out << time_point_to_string(tp);
		return out;
	}
}

_STD_END

#endif // _HULU_CHRONO_CHRONO_EX_H_