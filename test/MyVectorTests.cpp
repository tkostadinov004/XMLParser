#include "pch.h"
#include "CppUnitTest.h"
#include "../src/Utils/MyVector/MyVector.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MyVectorTests
{
	TEST_CLASS(MyVectorTests)
	{
		MyVector<int> s1;
	public:
		TEST_METHOD_INITIALIZE(Init)
		{
			s1.push_back(1);
			s1.push_back(2);
			s1.push_back(3);
		}
		TEST_METHOD(AreVectorsCopied)
		{
			MyVector<int> s2 = s1;

			Assert::AreEqual(s1.size(), s2.size());
			Assert::IsTrue(s1[0] == s2[0] && s1[1] && s2[1] && s1[2] && s2[2]);
		}
		TEST_METHOD(AreVectorsAssigned)
		{
			MyVector<int> s2;
			s2 = s1;

			Assert::AreEqual(s1.size(), s2.size());
			Assert::IsTrue(s1[0] == s2[0] && s1[1] && s2[1] && s1[2] && s2[2]);
		}
		TEST_METHOD(AtReturnsCorrectly)
		{
			for (size_t i = 0; i < s1.size(); i++)
			{
				Assert::AreEqual(s1.at(i), s1[i]);
			}
		}
		TEST_METHOD(AtThrowsOutOfRange)
		{
			MyVector<int> s1Copy = s1;
			Assert::ExpectException<std::out_of_range>([s1Copy]() {
				s1Copy.at(-1);
				});
			Assert::ExpectException<std::out_of_range>([s1Copy]() {
				s1Copy.at(s1Copy.size());
				});
			Assert::ExpectException<std::out_of_range>([s1Copy]() {
				s1Copy.at(s1Copy.size() + 1);
				});
		}
		TEST_METHOD(FrontReturnsCorrectly)
		{
			Assert::AreEqual(1, s1.front());
		}
		TEST_METHOD(FrontThrows)
		{
			MyVector<int> str;
			Assert::ExpectException<std::logic_error>([str]() {
				str.front();
				});
		}
		TEST_METHOD(BackReturnsCorrectly)
		{
			Assert::AreEqual(3, s1.back());
		}
		TEST_METHOD(BackThrows)
		{
			MyVector<int> str;
			Assert::ExpectException<std::logic_error>([str]() {
				str.back();
				});
		}
		TEST_METHOD(ReturnsLengthCorrectly)
		{
			Assert::AreEqual((size_t)3, s1.size());

			MyVector<int> str;
			Assert::AreEqual((size_t)0, str.size());
		}
		TEST_METHOD(ReturnsCapacityCorrectly)
		{
			Assert::AreEqual((size_t)4, s1.capacity());

			MyVector<int> str;
			Assert::AreEqual((size_t)1, str.capacity());
		}
		TEST_METHOD(ShrinksCorrectly)
		{
			s1.shrink_to_fit();
			Assert::AreEqual((size_t)3, s1.capacity());

			MyVector<int> str;
			str.shrink_to_fit();
			Assert::AreEqual((size_t)0, str.capacity());
		}
		TEST_METHOD(ClearsCorrectly)
		{
			s1.clear();
			Assert::AreEqual((size_t)0, s1.size());
		}
		TEST_METHOD(InsertsCorrectly)
		{
			MyVector<int> vect = s1;
			vect.insert(0, 5);
			Assert::IsTrue(vect.front() == 5);

			MyVector<int> vect1 = s1;
			vect1.insert(vect1.size(), 5);
			Assert::IsTrue(vect1.back() == 5);

			MyVector<int> vect2 = s1;
			vect2.insert(3, 5);
			Assert::IsTrue(vect1[3] == 5);

			MyVector<int> vect3;
			vect3.push_back(1);
			vect3.push_back(2);
			vect3.insert_range(0, vect3);
			Assert::IsTrue(vect3[0] == 1 && vect3[1] == 2 && vect3[2] == 1 && vect3[3] == 2);
		}
		TEST_METHOD(PushesCorrectly)
		{
			s1.push_back(4);
			Assert::IsTrue(s1[0] == 1 && s1[1] == 2 && s1[2] == 3 && s1[3] == 4);
		}
		TEST_METHOD(PopsCorrectly)
		{
			s1.pop_back();
			Assert::IsTrue(s1[0] == 1 && s1[1] == 2);
			Assert::AreEqual((size_t)2, s1.size());
			s1.pop_back();
			Assert::IsTrue(s1[0] == 1);
			Assert::AreEqual((size_t)1, s1.size());
			s1.pop_back();
			Assert::AreEqual((size_t)0, s1.size());
		}
		TEST_METHOD(PopThrows)
		{
			MyVector<int> str;
			Assert::ExpectException<std::logic_error>([&str]() {
				str.pop_back();
				});
		}
		TEST_METHOD(AppendsCorrectly)
		{
			s1.append(5, 2);
			Assert::IsTrue(s1[0] == 1 && s1[1] == 2 && s1[2] == 3 && s1[3] == 5 && s1[4] == 5);
		}
		TEST_METHOD(AnyWorksCorrectly)
		{
			Assert::IsTrue(s1.any([](const int& num) {return num == 1;}));
			Assert::IsTrue(s1.any([](const int& num) {return num == 2;}));
			Assert::IsTrue(s1.any([](const int& num) {return num == 3;}));
			Assert::IsFalse(s1.any([](const int& num) {return num == 4;}));
		}
		TEST_METHOD(ReturnsCountByConditionCorrectly)
		{
			MyVector<int> evens;
			for (size_t i = 0; i <= 10; i+=2)
			{
				evens.push_back(i);
			}
			Assert::AreEqual((size_t)6, evens.count([](const int& a) {return a % 2 == 0;}));
		}
		TEST_METHOD(FiltersByConditionCorrectly)
		{
			MyVector<int> nums;
			for (size_t i = 0; i <= 10; i++)
			{
				nums.push_back(i);
			}
			MyVector<int> evens = nums.filter([](const int& num) {return num % 2 == 0;});
			for (int i = 0; i <= 10; i += 2)
			{
				Assert::AreEqual(i, evens[i / 2]);
			}
		}
		/*TEST_METHOD(ComparesCorrectly)
		{
			Assert::IsTrue("abc" < "s");
			Assert::IsTrue("abc" == "abc");
			Assert::IsTrue("abc" != "ab");
			Assert::IsTrue("abc" <= "abc");
			Assert::IsTrue("abc" >= "abc");
			Assert::IsTrue("z" > "abc");
		}*/
	};
}
