#include "pch.h"
#include "CppUnitTest.h"
#include "loki/Typelist.h"
#include <string>
#include <vector>
#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace hulu;


namespace loki
{
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
	};
}
