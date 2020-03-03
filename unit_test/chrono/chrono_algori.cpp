#include "stdafx.h"
#include "CppUnitTest.h"
#include "chrono/chrono_algori.h"
#include <chrono>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace hulu;
using namespace std;

namespace chrono
{
	TEST_CLASS(chrono_algori_test)
	{
	public:

		/**
		 * @brief get the days base on 1970-1-1
		 */
		TEST_METHOD(days_from_civil_test)
		{			
			Assert::AreEqual(0, days_from_civil(1970, 1, 1));
			Assert::AreEqual(-1, days_from_civil(1969, 12, 31));
			Assert::AreEqual(1, days_from_civil(1970, 1, 2));

			// epoch from 1970-1-1 to 0000-3-1 is -719468
			Assert::AreEqual(-719468, days_from_civil(0000, 3, 1));
			Assert::AreEqual(-719528, days_from_civil(0, 1, 1));
		}

		/**
		 * @brief get the year/month/day from days base on 1970-1-1
		 */
		TEST_METHOD(civil_from_days_test)
		{
			auto epoch = civil_from_days(0);
			Assert::AreEqual(1970, get<0>(epoch));
			Assert::AreEqual((uint32_t)1, get<1>(epoch));
			Assert::AreEqual((uint32_t)1, get<2>(epoch));

			epoch = civil_from_days(-1);
			Assert::AreEqual(1969, get<0>(epoch));
			Assert::AreEqual((uint32_t)12, get<1>(epoch));
			Assert::AreEqual((uint32_t)31, get<2>(epoch));

			epoch = civil_from_days(1);
			Assert::AreEqual(1970, get<0>(epoch));
			Assert::AreEqual((uint32_t)1, get<1>(epoch));
			Assert::AreEqual((uint32_t)2, get<2>(epoch));

			epoch = civil_from_days(-719528);
			Assert::AreEqual(0, get<0>(epoch));
			Assert::AreEqual((uint32_t)1, get<1>(epoch));
			Assert::AreEqual((uint32_t)1, get<2>(epoch));

			epoch = civil_from_days(-719468);
			Assert::AreEqual(0, get<0>(epoch));
			Assert::AreEqual((uint32_t)3, get<1>(epoch));
			Assert::AreEqual((uint32_t)1, get<2>(epoch));
		}

		/**
		 * @brief check is leap year
		 */
		TEST_METHOD(is_leap_test)
		{
			Assert::IsTrue(is_leap(2020));
			Assert::IsFalse(is_leap(2019));
			Assert::IsFalse(is_leap(2018));
			Assert::IsFalse(is_leap(2017));
			Assert::IsTrue(is_leap(2016));
		}

		/**
		 * @brief get the last day of month that not leap year
		 */
		TEST_METHOD(last_day_of_month_common_year_test)
		{
			Assert::AreEqual(last_day_of_month_common_year(1), (unsigned)31);
			Assert::AreEqual(last_day_of_month_common_year(2), (unsigned)28);
			Assert::AreEqual(last_day_of_month_common_year(3), (unsigned)31);
			Assert::AreEqual(last_day_of_month_common_year(4), (unsigned)30);
			Assert::AreEqual(last_day_of_month_common_year(5), (unsigned)31);
			Assert::AreEqual(last_day_of_month_common_year(6), (unsigned)30);
			Assert::AreEqual(last_day_of_month_common_year(7), (unsigned)31);
			Assert::AreEqual(last_day_of_month_common_year(8), (unsigned)31);
			Assert::AreEqual(last_day_of_month_common_year(9), (unsigned)30);
			Assert::AreEqual(last_day_of_month_common_year(10), (unsigned)31);
			Assert::AreEqual(last_day_of_month_common_year(11), (unsigned)30);
			Assert::AreEqual(last_day_of_month_common_year(12), (unsigned)31);
		}

		/**
		 * @brief get the last day of month that is leap year
		 */
		TEST_METHOD(last_day_of_month_leap_year_test)
		{
			Assert::AreEqual(last_day_of_month_leap_year(1), (unsigned)31);
			Assert::AreEqual(last_day_of_month_leap_year(2), (unsigned)29);
			Assert::AreEqual(last_day_of_month_leap_year(3), (unsigned)31);
			Assert::AreEqual(last_day_of_month_leap_year(4), (unsigned)30);
			Assert::AreEqual(last_day_of_month_leap_year(5), (unsigned)31);
			Assert::AreEqual(last_day_of_month_leap_year(6), (unsigned)30);
			Assert::AreEqual(last_day_of_month_leap_year(7), (unsigned)31);
			Assert::AreEqual(last_day_of_month_leap_year(8), (unsigned)31);
			Assert::AreEqual(last_day_of_month_leap_year(9), (unsigned)30);
			Assert::AreEqual(last_day_of_month_leap_year(10), (unsigned)31);
			Assert::AreEqual(last_day_of_month_leap_year(11), (unsigned)30);
			Assert::AreEqual(last_day_of_month_leap_year(12), (unsigned)31);
		}

		/**
		 * @brief get the last day of year/month
		 */
		TEST_METHOD(last_day_of_month_test)
		{
			Assert::AreEqual(last_day_of_month(2020, 1), (unsigned)31);
			Assert::AreEqual(last_day_of_month(2020, 2), (unsigned)29);
			Assert::AreEqual(last_day_of_month(2020, 6), (unsigned)30);

			Assert::AreEqual(last_day_of_month(2015, 1), (unsigned)31);
			Assert::AreEqual(last_day_of_month(2015, 2), (unsigned)28);
			Assert::AreEqual(last_day_of_month(2015, 6), (unsigned)30);
		}

		/**
		 * @brief get the weekday for special days base on 1970-1-1
		 */
		TEST_METHOD(weekday_from_days_test)
		{
			auto day20200228 = days_from_civil(2020, 2, 28);
			Assert::AreEqual(weekday_from_days(day20200228), (unsigned)5); // friday
			Assert::AreEqual(weekday_from_days(day20200228 + 1), (unsigned)6);
			Assert::AreEqual(weekday_from_days(day20200228 - 1), (unsigned)4);
			Assert::AreEqual(weekday_from_days(day20200228 - 2), (unsigned)3);
			Assert::AreEqual(weekday_from_days(day20200228 - 3), (unsigned)2);
			Assert::AreEqual(weekday_from_days(day20200228 - 4), (unsigned)1);
			Assert::AreEqual(weekday_from_days(day20200228 - 5), (unsigned)0);
		}

		/**
		 * @brief get the difference days between two weekdays
		 */
		TEST_METHOD(weekday_difference_test)
		{
			constexpr unsigned a[7][7] =
			{// -       Sun Mon Tue Wed Thu Fri Sat
				/*Sun*/{ 0,  6,  5,  4,  3,  2,  1 },
				/*Mon*/{ 1,  0,  6,  5,  4,  3,  2 },
				/*Tue*/{ 2,  1,  0,  6,  5,  4,  3 },
				/*Wed*/{ 3,  2,  1,  0,  6,  5,  4 },
				/*Thu*/{ 4,  3,  2,  1,  0,  6,  5 },
				/*Fri*/{ 5,  4,  3,  2,  1,  0,  6 },
				/*Sat*/{ 6,  5,  4,  3,  2,  1,  0 }
			};
			for (unsigned x = 0; x < 7; ++x)
				for (unsigned y = 0; y < 7; ++y)
					Assert::IsTrue(weekday_difference(y, x) == a[x][y]);
		}

		/**
		 * @brief get the next day to a weekday
		 */
		TEST_METHOD(next_weekday_test)
		{
			Assert::AreEqual((unsigned)1, next_weekday(0));
			Assert::AreEqual((unsigned)4, next_weekday(3));
			Assert::AreEqual((unsigned)0, next_weekday(6));
		}

		/**
		 * @brief get the prior day to a weekday
		 */
		TEST_METHOD(prev_weekday_test)
		{
			Assert::AreEqual((unsigned)6, prev_weekday(0));
			Assert::AreEqual((unsigned)2, prev_weekday(3));
			Assert::AreEqual((unsigned)5, prev_weekday(6));
		}

		/**
		 * @brief overall test
		 */
		TEST_METHOD(chrono_algori_full_test)
		{
			static_assert(days_from_civil(1970, 1, 1) == 0, "1970-01-01 is day 0");
			Assert::IsTrue(civil_from_days(0) == make_tuple(1970, 1, 1));
			static_assert(weekday_from_days(days_from_civil(1970, 1, 1)) == 4, "1970-01-01 is a Thursday");

			int ystart = -1000;
			int prev_z = days_from_civil(ystart, 1, 1) - 1;
			Assert::IsTrue(prev_z < 0);
			int prev_wd = weekday_from_days(prev_z);
			Assert::IsTrue(0 <= prev_wd && prev_wd <= 6);
			auto t0 = std::chrono::system_clock::now();
			for (int y = ystart; y <= -ystart; ++y)
			{
				for (unsigned m = 1; m <= 12; ++m)
				{
					unsigned e = last_day_of_month(y, m);
					for (unsigned d = 1; d <= e; ++d)
					{
						int z = days_from_civil(y, m, d);
						Assert::IsTrue(prev_z < z);
						Assert::IsTrue(z == prev_z + 1);
						int yp;
						unsigned mp, dp;
						std::tie(yp, mp, dp) = civil_from_days(z);
						Assert::IsTrue(y == yp);
						Assert::IsTrue(m == mp);
						Assert::IsTrue(d == dp);
						unsigned wd = weekday_from_days(z);
						Assert::IsTrue(0 <= wd && wd <= 6);
						Assert::IsTrue(wd == next_weekday(prev_wd));
						Assert::IsTrue(prev_wd == prev_weekday(wd));
						prev_z = z;
						prev_wd = wd;
					}
				}
			}
		}
	};
}