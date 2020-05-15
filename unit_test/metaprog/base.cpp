#include "pch.h"
#include "CppUnitTest.h"
#include "meta_test/base.h"
#include "meta_test/algo.h"
#include <type_traits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace hulu;

namespace metaprog
{
	template <int Value1, int Value2>
	struct Plus
	{
		static constexpr int Value = Value1 + Value2;
	};

	struct Base {};
	struct Derived : Base {};

	template<typename T, typename U>
	using LargerType = typename IfThenElse<
		BoolType<(sizeof(T) > sizeof(U))>, T, U>::Result;


	TEST_CLASS(meta_test_base)
	{
	public:
		TEST_METHOD(print_test)
		{
			//__print(Plus<3, 4>::Value);
			//__print(IsEqual<IntType<5>, IntType<6>>::Result);
			//CompileError<IsEqual<IntType<6>, IntType<6>>::Result>();
		}

		TEST_METHOD(pointer_test)
		{
			Assert::IsTrue(std::is_same_v<
				int**, Pointer2Of<int>::Result
			>);

			Assert::IsTrue(std::is_same_v<
				int**, pointer_2_of_t<int>
			>);

			Assert::IsTrue(std::is_same_v<
				int*, pointer_of_t<int>
			>);
		}

		TEST_METHOD(times_test)
		{
			Assert::IsTrue(std::is_same_v<
				int***, Times<3, int, PointerOf>::Result
			>);

			Assert::IsTrue(std::is_same_v<
				int*****, Times_t<5, int, PointerOf>
			>);
		}

		TEST_METHOD(value_test)
		{
			Assert::AreEqual(11, __value(__int(5)) + __value(__int(6)));
			Assert::IsFalse(__value(__true()) && __value(__bool(false)));
			Assert::AreEqual(13, int_type_v<13>);
		}

		TEST_METHOD(arith_op_test)
		{
			int i = __value(__inc(__int(5)));
			int j = __value(__int(6));
			Assert::AreEqual(i, j);

			i = __value(__dec(__int(5)));
			j = __value(__int(4));
			Assert::AreEqual(i, j);

			i = __value(__add(__int(5), __int(2)));
			j = __value(__int(7));
			Assert::AreEqual(i, j);

			i = __value(__sub(__int(5), __int(2)));
			j = __value(__int(3));
			Assert::AreEqual(i, j);

			i = __value(__mul(__int(5), __int(2)));
			j = __value(__int(10));
			Assert::AreEqual(i, j);

			i = __value(__div(__int(5), __int(2)));
			j = __value(__int(2));
			Assert::AreEqual(i, j);

			i = __value(__mod(__int(5), __int(2)));
			j = __value(__int(1));
			Assert::AreEqual(i, j);
		}

		TEST_METHOD(logic1_op_test)
		{
			Assert::IsFalse(__value(__not(__bool(true))));
			Assert::IsFalse(__value(__and(__true(), __false())));
			Assert::IsTrue(__value(__or(__true(), __false())));
		}

		TEST_METHOD(is_convertible_test)
		{
			Assert::IsTrue(__value(__is_convertible(char, int)));
			Assert::IsFalse(__value(__is_convertible(char, void*)));
			Assert::IsTrue(__value(__is_convertible(char*, void*)));

			Assert::IsFalse(__value(__is_convertible(Base*, Derived*)));
			Assert::IsTrue(__value(__is_convertible(Derived*, Base*)));

			Assert::IsTrue(is_convertible_v<char, int>);
		}

		TEST_METHOD(IfThenElse_test)
		{
			Assert::IsTrue(std::is_same_v<typename IfThenElse<TrueType, int, long>::Result, int>);
			Assert::IsTrue(std::is_same_v<
				typename IfThenElse<BoolType<(sizeof(int) > sizeof(double))>, int, double>::Result,
				double>);
			Assert::IsTrue(std::is_same_v<LargerType<int, double>, double>);
			ASSERT_EQ(LargerType<int, double>, double);
		}

		TEST_METHOD(sum_test)
		{
			int i = __value(__sum());
			Assert::AreEqual(0, i);

			i = __value(__sum(__int(1), __int(2), __int(5)));
			Assert::AreEqual(8, i);
		}

		TEST_METHOD(ASSERT_TEST)
		{
			ASSERT_TRUE(BoolType<true>);
			ASSERT_FALSE(BoolType<false>);

			ASSERT_EQ(__int(0), __int(0));
			ASSERT_NE(__int(0), __int(1));
			ASSERT_EQ(__if(__true(), int, char), int);
			ASSERT_EQ(__if(__false(), int, char), char);
		}

		TEST("operator add on int type")
		{
			using num1 = __int(10);
			using num2 = __int(2);
			ASSERT_EQ(__add(num1, num2), __int(12));
		};
	};

	FIXTURE(TestIntTypeAlgo)
	{
		using num1 = __int(10);
		using num2 = __int(2);

		TEST("operator add on int type")
		{
			ASSERT_EQ(__add(num1, num2), __int(12));
		};

		TEST("operator sub on int type")
		{
			ASSERT_EQ(__sub(num1, num2), __int(8));
		};
	}

	FIXTURE(TestMetaFunctionInFixture)
	{
		template<typename T, typename U>
		using LargerType = typename IfThenElse<
			BoolType<(sizeof(T)>sizeof(U))>, T, U>::Result;

		struct TwoBytesType { char dummy[2]; };

		TEST("int should be larger than two bytes")
		{
			ASSERT_EQ(LargerType<char, int>, int);
		};

		TEST("char should be smaller than two bytes")
		{
			ASSERT_EQ(LargerType<char, TwoBytesType>, TwoBytesType);
		};
	}
}
