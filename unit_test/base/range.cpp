#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include "base/range.h"
#include <unordered_map>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace hulu::rx;

template <class Sink>
std::string to_string(Sink val) {
	return std::to_string(val);
}

namespace base
{
	TEST_CLASS(range1)
	{
	public:

		TEST_METHOD(operator_pipe)
		{
			std::string s = 123 | [](int x) {return to_string(x); };
			Assert::IsTrue(s == "123");
		}

		TEST_METHOD(range_take_advance_by_overflow)
		{
			auto bounds = seq() | take(10);
			advance_by(bounds, 11);
			Assert::IsTrue(bounds.i == bounds.n);

			auto arithmetic = seq() | take(10);
			advance_by(arithmetic, std::numeric_limits<size_t>::max());
			Assert::IsTrue(arithmetic.i == arithmetic.n);
		}

		TEST_METHOD(range_transform)
		{
			auto input = std::vector{ {1, 2, 3, 4} };
			auto strings = input | transform(&to_string<int>) | to_vector();
			auto expected = std::vector{ {"1", "2", "3", "4"} };
		}

		TEST_METHOD(range_transform_reentrant)
		{
			auto input = std::vector{ {1, 2, 3, 4} };
			auto strings = input | transform(&to_string<int>);
			auto a = strings | to_vector();
			auto b = strings | to_vector();
			Assert::IsTrue(a == b);
		}

		TEST_METHOD(range_filter)
		{
			auto input = std::list{ {1, 2, 3, 4} };
			auto odd = input | filter([](int x) { return x % 2 == 1; }) | to_list();
			for (auto x : odd) {
				Assert::IsTrue(x % 2 == 1);
			}
		}

		TEST_METHOD(range_filter_reentrant)
		{
			auto input = std::list{ {1, 2, 3, 4} };
			auto odd = input | filter([](int x) { return x % 2 == 1; });
			auto a = odd | to_vector();
			auto b = odd | to_vector();
			Assert::IsTrue(a == b);
		}

		TEST_METHOD(range_filter_idempotent) 
		{
			auto input = std::vector{ {1, 2, 3, 4} };
			int idempotent_guard{ 0 };
			auto odd = input | transform(
				[&idempotent_guard](int i) 
				{ 
					++idempotent_guard; 
					return i; 
				}
			)| filter([](int x) { return x % 2 == 1; });
			auto a = odd | to_vector();
			Assert::IsTrue(a == std::vector{ {1,3} });
			Assert::IsTrue(idempotent_guard == 4);
		}

		TEST_METHOD(range_first)
		{
			auto input = std::vector{ {"Hello", "World", "Morty"} };
			auto contains_y = [](std::string_view sv) { return sv.find('y') != std::string::npos; };
			RX_OPTIONAL morty = input | filter(contains_y) | first();
			Assert::IsTrue(morty.has_value());
			Assert::IsTrue(*morty == "Morty");
		}

		TEST_METHOD(range_first_reentrant) 
		{
			auto input = std::vector{ {"Hello", "World", "Morty"} };
			auto contains_y = [](std::string_view sv) { return sv.find('y') != std::string::npos; };
			auto range = input | filter(contains_y);
			auto a = range | first();
			auto b = range | first();
			Assert::IsTrue(a == b);
		}

		TEST_METHOD(range_first_n) 
		{
			auto input = std::vector{ {1, 2, 3, 4, 5} };
			auto first_3 = input | first_n(3) | to_vector();
			Assert::IsTrue(first_3.size() == 3);
			Assert::IsTrue(first_3 == std::vector{ 1, 2, 3});
		}

		TEST_METHOD(range_first_n_reentrant) 
		{
			auto input = std::vector{ {1, 2, 3, 4, 5} };
			auto first_3 = input | first_n(3);
			auto a = first_3 | to_vector();
			auto b = first_3 | to_vector();
			Assert::IsTrue(a == b);
		}

		TEST_METHOD(range_skip_n)
		{
			auto input = seq() | skip_n(1000) | first_n(10) | to_vector();
			auto expected = seq(1000) | first_n(10) | to_vector();
			Assert::IsTrue(input == expected);
		}

		TEST_METHOD(ranges_zip)
		{
			auto input1 = seq() | first_n(5);
			auto input2 = input1 | transform(&to_string<int>);
			auto input3 = seq(10); // inifinite range!
			auto zipped = zip(input1, input2, input3) | to_vector();
			Assert::IsTrue(zipped.size() == 5);
			auto expected = std::vector{
				std::make_tuple(0, "0", 10),
				std::make_tuple(1, "1", 11),
				std::make_tuple(2, "2", 12),
				std::make_tuple(3, "3", 13),
				std::make_tuple(4, "4", 14),
			};
		}

		TEST_METHOD(ranges_zip_two_same)
		{
			auto add = [](auto lr) {
				auto [l, r] = lr;
				return l + r;
			};
			auto value = zip(seq(0), seq(1)) | first_n(5) | transform(add) | max();
			Assert::IsTrue(value == 9);

			auto advancing = zip(seq(0), seq(1)) | transform(add);
			advance_by(advancing, 4);
			Assert::IsTrue(advancing.get() == 9);
		}

		TEST_METHOD(ranges_zip_advance_by) 
		{
			auto input = zip(seq(), seq(1));
			advance_by(input, 10);
			Assert::IsTrue(input.get() == std::tuple{ 10, 11 });

			auto finite = zip(seq(), seq() | take(5));
			size_t advanced = advance_by(finite, 6);
			Assert::IsTrue(advanced == 5);
		}

		TEST_METHOD(ranges_zip_reentrant)
		{
			auto input1 = seq() | first_n(5);
			auto input2 = input1 | transform(&to_string<int>);
			auto input3 = seq(10); // inifinite range!
			auto zipped = zip(input1, input2, input3);
			auto a = zipped | to_vector();
			auto b = zipped | to_vector();
			Assert::IsTrue(a == b);
			Assert::IsTrue(a.size() == 5);
		}

		TEST_METHOD(ranges_to_map)
		{
			auto input1 = seq();
			auto input2 = input1 | transform(&to_string<int>) | first_n(5);
			auto result = zip(input1, input2) | to_map();
			Assert::IsTrue(result.size() == 5);
			auto expected = std::map<int, std::string>{ {
				std::make_pair(0, "0"),
				std::make_pair(1, "1"),
				std::make_pair(2, "2"),
				std::make_pair(3, "3"),
				std::make_pair(4, "4"),
			} };
			Assert::IsTrue(result == expected);
		}

		TEST_METHOD(ranges_to_set)
		{
			auto input = std::vector{ {0, 0, 1, 1} };
			auto result = as_input_range(input) | to_set();
			Assert::IsTrue(result.size() == 2);
			auto expected = std::set{ {0, 1} };
			Assert::IsTrue(result == expected);
		}

		TEST_METHOD(ranges_append_to_arbitrary_container)
		{
			std::unordered_map<double, std::string> result;
			auto keys = seq();
			auto values = keys | transform(&to_string<int>);
			zip(keys, values) | first_n(5) | append(result);
			auto expected = std::unordered_map<double, std::string>{ {std::make_pair(0.0, "0"),
																	 std::make_pair(1.0, "1"),
																	 std::make_pair(2.0, "2"),
																	 std::make_pair(3.0, "3"),
																	 std::make_pair(4.0, "4")} };
			Assert::IsTrue(result == expected);
		}

		TEST_METHOD(range_append_to_rvalue_container)
		{
			std::string s;
			auto lower = seq<char>('a') | take(26) | append(s) ;
			Assert::IsTrue(lower == "abcdefghijklmnopqrstuvwxyz");

			auto digits = seq() | take(10) | append(std::list(0, 0));
			Assert::IsTrue(digits == std::list{ {0,1,2,3,4,5,6,7,8,9} });
		}

		TEST_METHOD(ranges_generate)
		{
			int x = 0;
			auto input = generate([&] { return x++; });
			auto result = input | first_n(5) | to_vector();
			auto expected = seq() | first_n(5) | to_vector();
			Assert::IsTrue(result == expected);
		}

		TEST_METHOD(ranges_generate_reentrant)
		{
			struct callable {
				int x = 0;
				int operator()() noexcept {
					return x++;
				}
			};
			// Check that the generator function is copied when sinking into a range.
			auto input = generate(callable{}) | first_n(5);
			auto a = input | to_vector();
			auto b = input | to_vector();
			Assert::IsTrue(a == b);
		}

		TEST_METHOD(ranges_until)
		{
			auto input = seq() | until([](int x) { return x == 5; });
			auto result = input | to_vector();
			auto expected = seq() | first_n(5) | to_vector();
			Assert::IsTrue(result == expected);
		}

		TEST_METHOD(ranges_any_of) {
			auto input = seq() | first_n(5);
			auto a = input | any_of([](int x) { return x > 3; });
			Assert::IsTrue(a);
			auto b = input | any_of([](int x) { return x == 5; });
			Assert::IsTrue(!b);
		}

		TEST_METHOD(ranges_all_of)
		{
			auto input = seq() | first_n(5);
			auto a = input | all_of([](int x) { return x < 5; });
			Assert::IsTrue(a);
			auto b = input | all_of([](int x) { return x < 4; });
			Assert::IsTrue(!b);
		}

		TEST_METHOD(ranges_none_of)
		{
			auto input = seq() | first_n(5);
			auto a = input | none_of([](int x) { return x > 4; });
			Assert::IsTrue(a);
			auto b = input | none_of([](int x) { return x == 4; });
			Assert::IsTrue(!b);
		}

		TEST_METHOD(ranges_avoid_copy)
		{
			auto input = std::vector{ {1, 2, 3, 4} };
			auto odd = input | filter([](int x) { return x % 2 == 1; });
			// modify the input to check that filtered range is not actually operating on a copy of the
			// vector. Note: filter() skips non-matching elements initially, which is a bit awkward.
			input[2] = 0;
			Assert::IsTrue((odd | count()) == 1);
		}

		TEST_METHOD(ranges_count_reentrant)
		{
			auto input = seq() | first_n(10);
			auto a = input | count();
			Assert::IsTrue(a == 10);
			auto b = input | count();
			Assert::IsTrue(b == 10);
		}

		TEST_METHOD(ranges_fill)
		{
			std::string a;
			fill_n(5, 'a') | append(a);
			Assert::IsTrue(a == std::string("aaaaa"));

			std::string b;
			fill('b') | first_n(5) | append(b);
			Assert::IsTrue(b == "bbbbb");

			int v = 7;
			Assert::IsTrue((fill(v) | take(5) | sum()) == 7 * 5);
			Assert::IsTrue(v == 7);
			Assert::IsTrue((fill_n(5, v) | sum()) == 7 * 5);
			Assert::IsTrue(v == 7);
		}

		TEST_METHOD(ranges_sum)
		{
			auto s = fill_n(5, 1) | sum();
			Assert::IsTrue(s == 5);

			auto d = fill_n(5, 1.0) | sum();
			Assert::IsTrue(d == 5.0);
		}

		TEST_METHOD(ranges_max)
		{
			auto s = seq() | first_n(5) | max();
			Assert::IsTrue(*s == 4);
		}

		TEST_METHOD(ranges_min)
		{
			auto s = seq() | first_n(5) | min();
			Assert::IsTrue(*s == 0);
		}

		TEST_METHOD(ranges_infinity_propagates)
		{
			auto s =
				seq() | skip_n(1) | filter([](auto) { return true; }) | transform([](auto) { return 0; });
			Assert::IsTrue(!decltype(s)::is_finite);
		}

		TEST_METHOD(ranges_enumerate_with_indices)
		{
			auto input = std::vector{ {"a", "b", "c"} };
			for (auto pair : zip(input, seq())) {
				if (std::get<0>(pair) == "a") {
					Assert::IsTrue(std::get<1>(pair) == 0);
				}
				else if (std::get<0>(pair) == "b") {
					Assert::IsTrue(std::get<1>(pair) == 1);
				}
				else if (std::get<0>(pair) == "c") {
					Assert::IsTrue(std::get<1>(pair) == 2);
				}
				else {
					Assert::IsTrue(false);
				}
			}

			auto a = zip(seq<size_t>(), input) | to_vector();
			auto b = enumerate(input) | to_vector();
			Assert::IsTrue(a == b);
		}

		TEST_METHOD(ranges_sort)
		{
			// Check that we can use std algorithms directly.
			auto sorted = std::vector{ {3, 2, 1} } | sort() | to_vector();
			Assert::IsTrue(std::is_sorted(begin(sorted), end(sorted)));

			auto odd = [](auto x) { return x % 2 == 1; };

			// Chaining
			auto filtered_sorted = std::vector{ {3, 2, 1} } | filter(odd) | sort() | to_vector();
			Assert::IsTrue(std::is_sorted(begin(filtered_sorted), end(filtered_sorted)));
		}

		TEST_METHOD(ranges_reverse)
		{
			auto input = std::vector{ {2, 3, 6, 1, 7, 8, 3, 4} };
			auto result = input | sort() | reverse() | to_vector();
			auto expected = std::vector{ {8, 7, 6, 4, 3, 3, 2, 1} };
			Assert::IsTrue(result == expected);
		}

		TEST_METHOD(ranges_in_groups_of_exactly_dynamic_size)
		{
			auto input = seq<float>() | take(1001) | to_vector();

			size_t num_groups = input | in_groups_of_exactly(4) | count();
			Assert::IsTrue(num_groups == 250);

			// In optimized builds, compilers should be able to auto-vectorize this.
			std::array<float, 4> sums = { 0.f, 0.f, 0.f, 0.f };
			for (auto group : input | in_groups_of_exactly(4)) {
				std::get<0>(sums) += group.get();
				group.next();
				std::get<1>(sums) += group.get();
				group.next();
				std::get<2>(sums) += group.get();
				group.next();
				std::get<3>(sums) += group.get();
				group.next();
			}

			std::array<float, 4> expected_sums = { 0.f, 0.f, 0.f, 0.f };
			for (auto [i, x] : enumerate(input)) {
				if (i != 1000)
					expected_sums[i % 4] += x;
			}

			Assert::IsTrue(sums == expected_sums);
		}

		TEST_METHOD(ranges_in_groups_of_exactly_advance_by)
		{
			auto input = seq() | in_groups_of_exactly(4);
			size_t advanced = advance_by(input, 3);  // already at the first group
			auto group = input.get();
			Assert::IsTrue(group.get() == 16);
			Assert::IsTrue(advanced == 3);

			auto finite = seq() | take(11) | in_groups_of_exactly(4);
			advanced = advance_by(finite, 2);
			Assert::IsTrue(finite.at_end());
			Assert::IsTrue(advanced == 1);
		}

		TEST_METHOD(ranges_group_adjacent_by) 
		{
			const auto input = seq() | take(10);

			auto pred = [](int x) { return x / 3; };

			auto groups = input | group_adjacent_by(pred);
			auto tmp = groups | to_vector();
			size_t num_groups = groups | count();
			Assert::IsTrue(num_groups == 4);

			int previous = std::numeric_limits<int>::max();
			for (const auto& group : groups) {
				for (auto x : group) {
					Assert::IsTrue(pred(x) == pred(group.get()));
					Assert::IsTrue(pred(x) != previous);
				}
				previous = pred(group.get());
			}

			auto group_vectors = groups | transform(to_vector()) | to_vector();
			Assert::IsTrue(group_vectors.size() == 4);
			Assert::IsTrue(group_vectors[0] == std::vector{ {0, 1, 2} });
			Assert::IsTrue(group_vectors[1] == std::vector{ {3, 4, 5} });
			Assert::IsTrue(group_vectors[2] == std::vector{ {6, 7, 8} });
			Assert::IsTrue(group_vectors[3] == std::vector(1, 9)); // note: initializer lists are broken
		}

		TEST_METHOD(ranges_non_default_constructible)
		{
			struct Foo {
				const int x;
				constexpr explicit Foo(int x) : x(x) {}
				bool operator<(const Foo& other) const noexcept {
					return x < other.x;
				}
			};
			static_assert(!std::is_default_constructible_v<Foo>);

			auto generate_foos = seq() | transform([](int x) { return Foo{ x }; });

			auto vec = generate_foos | filter([](const Foo& foo) { return bool(foo.x % 2); })
				| transform([](const Foo& foo) { return Foo{ foo.x + 1 }; }) | take(10) | to_vector();
			static_cast<void>(vec);

			std::vector<Foo> vec2;
			generate_foos | take(10) | append(vec2);
		}

		TEST_METHOD(ranges_first_after_sort)
		{
			auto result = std::vector{ {4, 3, 2, 1} } | sort() | first();
			Assert::IsTrue(result == 1);
		}

		TEST_METHOD(ranges_non_default_constructible_non_copyable_predicate)
		{
			// A compare predicate that is not default-constructible or copyable.
			struct Compare : std::less<void> {
				constexpr explicit Compare(int) {}
				constexpr Compare(Compare&&) {}
				constexpr Compare& operator=(Compare&&) { return *this; }
				constexpr Compare(const Compare&) = delete;
				constexpr Compare& operator=(const Compare&) = delete;
			};
			static_assert(!std::is_default_constructible_v<Compare>);

			auto in = seq() | take(10);
			auto vec = in | sort(Compare{ 0 }) | to_vector();
			Assert::IsTrue(vec == (in | to_vector()));

			Assert::IsTrue((in | sort(Compare{ 0 }) | max(Compare{ 0 })) == 9);
			Assert::IsTrue((in | sort(Compare{ 0 }) | min(Compare{ 0 })) == 0);

			// Compile-time check that iterators don't introduce default-constructibility as a requirement.
			// Note: Explicit call to as_input_range() is required here because range-based for loops do not
			//       perfectly-forward to `begin()/end()` (and it would usually be wrong if they did).
			for (auto x : as_input_range(in | sort(Compare{ 0 }))) {
				static_cast<void>(x);
			}
		}

		TEST_METHOD(ranges_empty_range)
		{
			Assert::IsTrue((empty_range() | count()) == 0);
			Assert::IsTrue((empty_range() | to_vector()) == std::vector<void*>());
		}

		TEST_METHOD(ranges_chain)
		{
			// 0 arguments
			static_assert(std::is_same_v<decltype(chain()), decltype(empty_range())>);

			// 1 argument
			static_assert(std::is_same_v<decltype(chain(seq())), decltype(seq())>);

			// 2 arguments
			std::string sap;
			auto homogenous_actual = chain("hello", "world") | to_vector();
			auto homogenous_expected = "helloworld";
			//Assert::IsTrue(sap == homogenous_expected);

			// 3 arguments
			//auto heterogeneous_actual = chain(seq() | take(4), "test", seq()) | take(10) | to_vector();
			//auto heterogeneous_expected = std::vector<int>{ {0,1,2,3,'t','e','s','t',0,1} };
			//Assert::IsTrue(heterogeneous_actual == heterogeneous_expected);

			// Ensure ranges in between can be empty.
			//std::string sap2;
			//homogenous_actual = chain("", "hello", "world") | append(sap2);
			//Assert::IsTrue(sap2 == homogenous_expected);

			//std::string sap3;
			//homogenous_actual = chain("hello", "", "world") | append(sap3);
			//Assert::IsTrue(sap3 == homogenous_expected);

			//std::string sap4;
			//homogenous_actual = chain("hello", "world", "") | append(sap4);
			//Assert::IsTrue(sap4 == homogenous_expected);
		}

	};
}
