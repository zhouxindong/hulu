#include "pch.h"
#include "CppUnitTest.h"
#include "loki/Typelist.h"
#include <string>
#include <vector>
#include <type_traits>
#include <typeinfo>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace hulu;


namespace loki
{
	class Widget {};

	class ScrollBar : public Widget {};

	class Button : public Widget {};

	class GraphicButton : public Button {};

	TEST_CLASS(Typelist_test)
	{
	public:

		TEST_METHOD(length_test)
		{
			Assert::AreEqual(0, Typelist_length_v<Typelist<>>);
			Assert::AreEqual(1, Typelist_length_v<Typelist<int>>);
			Assert::AreEqual(2, Typelist_length_v<Typelist<int, double>>);
			Assert::AreEqual(3, Typelist_length_v<Typelist<int, char, float>>);
			Assert::AreEqual(4, Typelist_length_v<Typelist<short, float, long, long long>>);
			Assert::AreEqual(5, Typelist_length_v<Typelist<std::string, std::vector<int>, std::vector<float>,
				std::vector<std::string>, std::vector<std::vector<int>>>>);
		}

		TEST_METHOD(at_test)
		{
			Assert::IsTrue(std::is_same_v<int, Typelist_at_t<Typelist<int>, 0>>);
			Assert::IsTrue(std::is_same_v<short, Typelist_at_t<Typelist<short, float, long, long long>, 0>>);
			Assert::IsTrue(std::is_same_v<float, Typelist_at_t<Typelist<short, float, long, long long>, 1>>);
			Assert::IsTrue(std::is_same_v<long, Typelist_at_t<Typelist<short, float, long, long long>, 2>>);
			Assert::IsTrue(std::is_same_v<long long, Typelist_at_t<Typelist<short, float, long, long long>, 3>>);
			Assert::IsTrue(std::is_same_v<NullType, Typelist_at_t<Typelist<>, 0>>);
			Assert::IsTrue(std::is_same_v<NullType, Typelist_at_t<Typelist<int>, 1>>);
		}

		TEST_METHOD(index_of_test)
		{
			Assert::AreEqual(-1, Typelist_index_of_v<Typelist<>, int>);
			Assert::AreEqual(-1, Typelist_index_of_v<Typelist<char, short, int, float, double, long>, std::string>);
			Assert::AreEqual(0, Typelist_index_of_v<Typelist<char, short, int, float, double, long>, char>);
			Assert::AreEqual(1, Typelist_index_of_v<Typelist<char, short, int, float, double, long>, short>);
			Assert::AreEqual(2, Typelist_index_of_v<Typelist<char, short, int, float, double, long>, int>);
			Assert::AreEqual(3, Typelist_index_of_v<Typelist<char, short, int, float, double, long>, float>);
			Assert::AreEqual(4, Typelist_index_of_v<Typelist<char, short, int, float, double, long>, double>);
			Assert::AreEqual(5, Typelist_index_of_v<Typelist<char, short, int, float, double, long>, long>);
		}

		TEST_METHOD(append_test)
		{
			Assert::IsTrue(std::is_same_v<
				Typelist<int>,
				Typelist_append_t<Typelist<>, int>
			>);

			Assert::IsTrue(std::is_same_v<
				Typelist<int, double, float>,
				Typelist_append_t<Typelist<int, double>, float>
			>);

			Assert::IsTrue(std::is_same_v<
				Typelist<int, double, float>,
				Typelist_append_t<Typelist<int>, Typelist<double, float>>
			>);
		}

		TEST_METHOD(erase_test)
		{
			Assert::IsTrue(std::is_same_v<Typelist<>, Typelist_erase_t<Typelist<>, int>>);
			Assert::IsTrue(std::is_same_v<Typelist<>, Typelist_erase_t<Typelist<int>, int>>);
			Assert::IsTrue(std::is_same_v<Typelist<int, float>, Typelist_erase_t<Typelist<double, int, float>, double>>);
			Assert::IsTrue(std::is_same_v<Typelist<double, float>, Typelist_erase_t<Typelist<double, int, float>, int>>);
			Assert::IsTrue(std::is_same_v<Typelist<double, int>, Typelist_erase_t<Typelist<double, int, float>, float>>);
			Assert::IsTrue(std::is_same_v<Typelist<double, int, float>, Typelist_erase_t<Typelist<double, int, float>, short>>);
		}

		TEST_METHOD(erase_all_test)
		{
			Assert::IsTrue(std::is_same_v<Typelist<>, Typelist_erase_all_t<Typelist<>, int>>);
			Assert::IsTrue(std::is_same_v<Typelist<>, Typelist_erase_all_t<Typelist<int>, int>>);
			Assert::IsTrue(std::is_same_v<Typelist<>, Typelist_erase_all_t<Typelist<int, int>, int>>);
			Assert::IsTrue(std::is_same_v<Typelist<>, Typelist_erase_all_t<Typelist<int, int, int>, int>>);
			Assert::IsTrue(std::is_same_v<Typelist<float>, Typelist_erase_all_t<Typelist<int, float>, int>>);
			Assert::IsTrue(std::is_same_v<Typelist<float>, Typelist_erase_all_t<Typelist<float, int>, int>>);
			Assert::IsTrue(std::is_same_v<Typelist<float>, Typelist_erase_all_t<Typelist<int, float, int>, int>>);
			Assert::IsTrue(std::is_same_v<Typelist<float>, Typelist_erase_all_t<Typelist<int, int, float>, int>>);
			Assert::IsTrue(std::is_same_v<Typelist<float>, Typelist_erase_all_t<Typelist<float, int, int>, int>>);
			Assert::IsTrue(std::is_same_v<Typelist<float, double>, Typelist_erase_all_t<Typelist<float, int, double, int>, int>>);
		}

		TEST_METHOD(unique_test)
		{
			Assert::IsTrue(std::is_same_v<Typelist<>, Typelist_unique_t<Typelist<>>>);
			Assert::IsTrue(std::is_same_v<Typelist<int>, Typelist_unique_t<Typelist<int>>>);
			Assert::IsTrue(std::is_same_v<Typelist<int>, Typelist_unique_t<Typelist<int, int>>>);
			Assert::IsTrue(std::is_same_v<Typelist<int>, Typelist_unique_t<Typelist<int, int, int, int, int, int>>>);
			Assert::IsTrue(std::is_same_v<Typelist<int, double, float>,
				Typelist_unique_t<Typelist<int, double, float, float, double, int, int, float>>>);
		}

		TEST_METHOD(replace_test)
		{
			Assert::IsTrue(std::is_same_v<Typelist<>, Typelist_replace_t<Typelist<>, int, long>>);
			Assert::IsTrue(std::is_same_v<Typelist<long>, Typelist_replace_t<Typelist<long>, int, long>>);
			Assert::IsTrue(std::is_same_v<Typelist<long, int>, Typelist_replace_t<Typelist<int, int>, int, long>>);
			Assert::IsTrue(std::is_same_v<Typelist<double, long, int>, Typelist_replace_t<Typelist<double, int, int>, int, long>>);
		}

		TEST_METHOD(replace_all_test)
		{
			Assert::IsTrue(std::is_same_v<Typelist<>, Typelist_replace_all_t<Typelist<>, int, long>>);
			Assert::IsTrue(std::is_same_v<Typelist<long>, Typelist_replace_all_t<Typelist<long>, int, long>>);
			Assert::IsTrue(std::is_same_v<Typelist<long, long>, Typelist_replace_all_t<Typelist<int, int>, int, long>>);
			Assert::IsTrue(std::is_same_v<Typelist<double, long, long>, Typelist_replace_all_t<Typelist<double, int, int>, int, long>>);
		}

		TEST_METHOD(front_test)
		{
			Assert::IsTrue(std::is_same_v<NullType, Typelist_front_t<Typelist<>>>);
			Assert::IsTrue(std::is_same_v<std::string, Typelist_front_t<Typelist<std::string>>>);
			Assert::IsTrue(std::is_same_v<double, Typelist_front_t<Typelist<double, float, std::string>>>);
		}

		TEST_METHOD(pop_front_test)
		{
			Assert::IsTrue(std::is_same_v<Typelist<>, Typelist_pop_front_t<Typelist<>>>);
			Assert::IsTrue(std::is_same_v<Typelist<int>, Typelist_pop_front_t<Typelist<double, int>>>);
			Assert::IsTrue(std::is_same_v<Typelist<int, float>, Typelist_pop_front_t<Typelist<int, int, float>>>);
		}

		TEST_METHOD(prepend_test)
		{
			Assert::IsTrue(std::is_same_v<Typelist<int>, Typelist_prepend_t<Typelist<>, int>>);
			Assert::IsTrue(std::is_same_v<Typelist<double, int>, Typelist_prepend_t<Typelist<int>, double>>);
			Assert::IsTrue(std::is_same_v<Typelist<double, double>, Typelist_prepend_t<Typelist<double>, double>>);
			Assert::IsTrue(std::is_same_v<Typelist<double, double, double>, Typelist_prepend_t<Typelist<double, double>, double>>);
		}

		TEST_METHOD(largest_type_test)
		{
			Assert::IsTrue(std::is_same_v<char, Typelist_largest_type_t<Typelist<>>>);
			Assert::IsTrue(std::is_same_v<int, Typelist_largest_type_t<Typelist<char, int, short>>>);
			Assert::IsTrue(std::is_same_v<double, Typelist_largest_type_t<Typelist<char, int, double, short, long long>>>);
		}

		TEST_METHOD(is_empty_test)
		{
			Assert::IsTrue(Typelist_is_empty_v<Typelist<>>);
			Assert::IsFalse(Typelist_is_empty_v<Typelist<int>>);
		}

		TEST_METHOD(reverse_test)
		{
			Assert::IsTrue(std::is_same_v<Typelist<>, Typelist_reverse_t<Typelist<>>>);
			Assert::IsTrue(std::is_same_v<Typelist<int>, Typelist_reverse_t<Typelist<int>>>);
			Assert::IsTrue(std::is_same_v<Typelist<int, double>, Typelist_reverse_t<Typelist<double, int>>>);
			Assert::IsTrue(std::is_same_v<Typelist<int, double, int>, Typelist_reverse_t<Typelist<int, double, int>>>);
		}

		TEST_METHOD(pop_back_test)
		{
			Assert::IsTrue(std::is_same_v<Typelist<>, Typelist_pop_back_t<Typelist<>>>);
			Assert::IsTrue(std::is_same_v<Typelist<>, Typelist_pop_back_t<Typelist<int>>>);
			Assert::IsTrue(std::is_same_v<Typelist<int>, Typelist_pop_back_t<Typelist<int, double>>>);
			Assert::IsTrue(std::is_same_v<Typelist<char, double, float>, Typelist_pop_back_t<Typelist<char, double, float, short>>>);
		}

		TEST_METHOD(most_derived_test)
		{
			Assert::IsTrue(std::is_same_v<Widget, Typelist_most_derived_t<Typelist<>, Widget>>);
			Assert::IsTrue(std::is_same_v<Widget, Typelist_most_derived_t<Typelist<Widget>, Widget>>);
			Assert::IsTrue(std::is_same_v<ScrollBar, Typelist_most_derived_t<Typelist<Widget, ScrollBar>, Widget>>);
			Assert::IsTrue(std::is_same_v<GraphicButton, Typelist_most_derived_t<Typelist<Widget, GraphicButton, Button>, Widget>>);
			Assert::IsTrue(std::is_same_v<GraphicButton, Typelist_most_derived_t<Typelist<ScrollBar, Widget, GraphicButton, Button>, Widget>>);
			Assert::IsTrue(std::is_same_v<GraphicButton, Typelist_most_derived_t<Typelist<ScrollBar, GraphicButton>, Widget>>);
		}

		TEST_METHOD(derived_to_front_test)
		{
			Assert::IsTrue(std::is_same_v<Typelist<>, Typelist_derived_to_front_t<Typelist<>>>);
			Assert::IsTrue(std::is_same_v<Typelist<ScrollBar>, Typelist_derived_to_front_t<Typelist<ScrollBar>>>);
			Assert::IsTrue(std::is_same_v<Typelist<ScrollBar, Widget>, Typelist_derived_to_front_t<Typelist<Widget, ScrollBar>>>);
			Assert::IsTrue(std::is_same_v<Typelist<GraphicButton, Button, Widget>,
				Typelist_derived_to_front_t<Typelist<Widget, Button, GraphicButton>>>);
			Assert::IsTrue(std::is_same_v<Typelist<GraphicButton, Button, Widget>,
				Typelist_derived_to_front_t<Typelist<Widget, GraphicButton, Button>>>);
			Assert::IsTrue(std::is_same_v<Typelist<GraphicButton, Button, Widget>,
				Typelist_derived_to_front_t<Typelist<Button, Widget, GraphicButton>>>);
			Assert::IsTrue(std::is_same_v<Typelist<GraphicButton, Button, Widget>,
				Typelist_derived_to_front_t<Typelist<Button, GraphicButton, Widget>>>);
			Assert::IsTrue(std::is_same_v<Typelist<GraphicButton, Button, Widget>,
				Typelist_derived_to_front_t<Typelist<GraphicButton, Button, Widget>>>);
			Assert::IsTrue(std::is_same_v<Typelist<GraphicButton, Button, Widget>,
				Typelist_derived_to_front_t<Typelist<GraphicButton, Widget, Button>>>);
		}
	};
}
