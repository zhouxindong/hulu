#include "stdafx.h"
#include "CppUnitTest.h"

#include "chrono/chrono_ex.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace hulu;
using namespace std;

namespace chrono
{
	TEST_CLASS(chrono_ex_test)
	{
	public:

		TEST_METHOD(time_zone_test)
		{
			Assert::AreEqual(-480l, time_zone());
		}

		TEST_METHOD(to_utc_local_test)
		{
			auto now = std::chrono::system_clock::now();
			auto tp_l = to_local(now);
			auto tp_u = to_utc(tp_l);
			auto l1 = now.time_since_epoch().count();
			auto l2 = tp_u.time_since_epoch().count();
			Assert::AreEqual((uint64_t)l1, (uint64_t)l2);
		}

		TEST_METHOD(to_time_point_test)
		{
			std::chrono::system_clock::time_point tp = to_time_point(1970, 1, 1);
			auto a = tp.time_since_epoch().count();
			Assert::AreEqual((uint64_t)0, (uint64_t)a);

			tp = to_time_point(1969, 12, 31, 12);
			auto diff = tp - std::chrono::system_clock::time_point();
			auto seconds = std::chrono::duration_cast<std::chrono::seconds>(diff);
			Assert::IsTrue(-43200 == seconds.count());

			auto d1950 = to_time_point(1950, 1, 1).time_since_epoch().count();
			auto d2000 = to_time_point(2000, 1, 1).time_since_epoch().count();
			Assert::IsTrue(d1950 == -6311520000000000ll);
			Assert::IsTrue(d2000 == 9466848000000000ll);
		}

		TEST_METHOD(proleptic_gregorian_epoch_test)
		{
			Assert::AreEqual(-719528, proleptic_gregorian_epoch().count());
		}

		TEST_METHOD(tokenize_time_point_test)
		{
			using namespace std;
			auto now = std::chrono::system_clock::now();
			auto tu = tokenize_time_point(now);
			auto tl = tokenize_time_point(to_local(now));
			auto tu2 = tokenize_time_point(to_utc(to_local(now)));

			Assert::AreEqual(get<0>(tu2), get<0>(tu));
			Assert::AreEqual(get<1>(tu2), get<1>(tu));
			Assert::AreEqual(get<2>(tu2), get<2>(tu));
			Assert::AreEqual(get<3>(tu2), get<3>(tu));
			Assert::AreEqual(get<4>(tu2), get<4>(tu));
			Assert::AreEqual(get<5>(tu2), get<5>(tu));
			Assert::AreEqual(get<6>(tu2), get<6>(tu));

			auto d1969 = to_time_point(1969, 12, 31, 12);
			auto t1969 = tokenize_time_point(d1969);
			Assert::IsTrue(1969 == get<0>(t1969));
			Assert::IsTrue(12 == get<1>(t1969));
			Assert::IsTrue(31 == get<2>(t1969));
			Assert::IsTrue(12 == get<3>(t1969));
			Assert::IsTrue(0 == get<4>(t1969));
			Assert::IsTrue(0 == get<5>(t1969));
			Assert::IsTrue(0 == get<6>(t1969));

			auto d1970 = to_time_point(1969, 11, 14);
			auto t1970 = tokenize_time_point(d1970);
			Assert::IsTrue(1969 == get<0>(t1970));
			Assert::IsTrue(11 == get<1>(t1970));
			Assert::IsTrue(14 == get<2>(t1970));
			Assert::IsTrue(0 == get<3>(t1970));
			Assert::IsTrue(0 == get<4>(t1970));
			Assert::IsTrue(0 == get<5>(t1970));
			Assert::IsTrue(0 == get<6>(t1970));


			auto d1950 = to_time_point(1950, 3, 12, 14, 38, 49, 285);
			auto t1950 = tokenize_time_point(d1950);
			Assert::IsTrue(1950 == get<0>(t1950));
			Assert::IsTrue(3 == get<1>(t1950));
			Assert::IsTrue(12 == get<2>(t1950));
			Assert::IsTrue(14 == get<3>(t1950));
			Assert::IsTrue(38 == get<4>(t1950));
			Assert::IsTrue(49 == get<5>(t1950));
			Assert::IsTrue(285 == get<6>(t1950));

			auto d2000 = to_time_point(2000, 11, 22, 1, 58, 9, 882);
			auto t2000 = tokenize_time_point(d2000);

			Assert::IsTrue(2000 == get<0>(t2000));
			Assert::IsTrue(11 == get<1>(t2000));
			Assert::IsTrue(22 == get<2>(t2000));
			Assert::IsTrue(1 == get<3>(t2000));
			Assert::IsTrue(58 == get<4>(t2000));
			Assert::IsTrue(9 == get<5>(t2000));
			Assert::IsTrue(882 == get<6>(t2000));

			auto dd = to_time_point(1970, 1, 1);
			auto tt = tokenize_time_point(dd);
			Assert::IsTrue(1970 == get<0>(tt));
			Assert::IsTrue(1 == get<1>(tt));
			Assert::IsTrue(1 == get<2>(tt));
			Assert::IsTrue(0 == get<3>(tt));
			Assert::IsTrue(0 == get<4>(tt));
			Assert::IsTrue(0 == get<5>(tt));
			Assert::IsTrue(0 == get<6>(tt));
		}

		TEST_METHOD(time_point_to_string_test)
		{
			using namespace std;
			auto d1950 = to_time_point(1950, 3, 12, 14, 38, 49, 285);
			string s1 = time_point_to_string(d1950);
			Assert::IsTrue(std::string("1950-03-12 14:38:49.285") == s1);
			auto d2000 = to_time_point(2000, 11, 22, 1, 58, 9, 882);
			string s2 = time_point_to_string(d2000);
			Assert::IsTrue(std::string("2000-11-22 01:58:09.882") == s2);
		}

		TEST_METHOD(time_point_to_sec_test)
		{
			auto sec1950 = time_point_to_sec(to_time_point(1950, 1, 1));
			Assert::IsTrue(sec1950 == -631152000);
			auto sec2000 = time_point_to_sec(to_time_point(2000, 1, 1));
			Assert::IsTrue(sec2000 == 946684800);
		}

		TEST_METHOD(time_point_to_ms_test)
		{
			auto sec1950 = time_point_to_ms(to_time_point(1950, 1, 1));
			Assert::IsTrue(sec1950 == -631152000000);
			auto sec2000 = time_point_to_ms(to_time_point(2000, 1, 1));
			Assert::IsTrue(sec2000 == 946684800000);
		}

		TEST_METHOD(sec_to_time_point_test)
		{
			auto tp = sec_to_time_point(-631152000);
			auto tup = tokenize_time_point(tp);
			Assert::IsTrue(1950 == get<0>(tup));
			Assert::IsTrue(1 == get<1>(tup));
			Assert::IsTrue(1 == get<2>(tup));
			Assert::IsTrue(0 == get<3>(tup));
			Assert::IsTrue(0 == get<4>(tup));
			Assert::IsTrue(0 == get<5>(tup));
			Assert::IsTrue(0 == get<6>(tup));

			tp = sec_to_time_point(946684800);
			tup = tokenize_time_point(tp);
			Assert::IsTrue(2000 == get<0>(tup));
			Assert::IsTrue(1 == get<1>(tup));
			Assert::IsTrue(1 == get<2>(tup));
			Assert::IsTrue(0 == get<3>(tup));
			Assert::IsTrue(0 == get<4>(tup));
			Assert::IsTrue(0 == get<5>(tup));
			Assert::IsTrue(0 == get<6>(tup));
		}

		TEST_METHOD(ms_to_time_point_test)
		{
			auto tp = ms_to_time_point(-631152000000);
			auto tup = tokenize_time_point(tp);
			Assert::IsTrue(1950 == get<0>(tup));
			Assert::IsTrue(1 == get<1>(tup));
			Assert::IsTrue(1 == get<2>(tup));
			Assert::IsTrue(0 == get<3>(tup));
			Assert::IsTrue(0 == get<4>(tup));
			Assert::IsTrue(0 == get<5>(tup));
			Assert::IsTrue(0 == get<6>(tup));

			tp = ms_to_time_point(946684800000);
			tup = tokenize_time_point(tp);
			Assert::IsTrue(2000 == get<0>(tup));
			Assert::IsTrue(1 == get<1>(tup));
			Assert::IsTrue(1 == get<2>(tup));
			Assert::IsTrue(0 == get<3>(tup));
			Assert::IsTrue(0 == get<4>(tup));
			Assert::IsTrue(0 == get<5>(tup));
			Assert::IsTrue(0 == get<6>(tup));
		}

		TEST_METHOD(chrono_ex_key_test)
		{
			// this test would be execute about 2 mins
			int year = 1970;
			for (int mon = 1; mon < 13; ++mon)
			{
				for (int day = 1; day < 29; ++day)
				{
					for (int hour = 0; hour < 24; ++hour)
					{
						for (int min = 0; min < 60; ++min)
						{
							for (int sec = 0; sec < 60; ++sec)
							{
								auto tp = to_time_point(year, mon, day, hour, min, sec);
								auto tk = tokenize_time_point(tp);
								Assert::IsTrue(year == get<0>(tk));
								Assert::IsTrue(mon == get<1>(tk));
								Assert::IsTrue(day == get<2>(tk));
								Assert::IsTrue(hour == get<3>(tk));
								Assert::IsTrue(min == get<4>(tk));
								Assert::IsTrue(sec == get<5>(tk));
								Assert::IsTrue(0 == get<6>(tk));
							}
						}
					}
				}
			}
		}

		TEST_METHOD(chrono_ex_error_test)
		{
			auto tp = to_time_point(1921, 2, 30, 25, 89, 71, 382);
			auto tu = tokenize_time_point(tp);
			Assert::IsTrue(1921 == get<0>(tu));
			Assert::IsTrue(3 == get<1>(tu));
			Assert::IsTrue(3 == get<2>(tu));
			Assert::IsTrue(2 == get<3>(tu));
			Assert::IsTrue(30 == get<4>(tu));
			Assert::IsTrue(11 == get<5>(tu));
			Assert::IsTrue(382 == get<6>(tu));
		}
	};
}