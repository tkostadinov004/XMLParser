#include "pch.h"
#include "CppUnitTest.h"
#include "../src/Utils/MyString/MyString.cpp"
#include "../src/Utils/Iterators/StringIterator.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MyStringTests
{
	TEST_CLASS(MyStringTests)
	{
		MyString s1;	
	public:
		TEST_METHOD_INITIALIZE(Init)
		{
			s1 = "test";
		}
		TEST_METHOD(AreStringsCopied)
		{
			MyString s2 =s1;

			Assert::IsTrue(strcmp(s1.c_str(), s2.c_str()) == 0);
			Assert::AreEqual(s1.length(), s2.length());
			Assert::IsTrue(s1.c_str() != s2.c_str());
		}
		TEST_METHOD(AreStringsAssigned)
		{
			MyString s2;
			s2 = s1;

			Assert::IsTrue(strcmp(s1.c_str(), s2.c_str()) == 0);
			Assert::AreEqual(s1.length(), s2.length());
			Assert::IsTrue(s1.c_str() != s2.c_str());
		}
		TEST_METHOD(AtReturnsCorrectly)
		{
			for (size_t i = 0; i < s1.length(); i++)
			{
				Assert::AreEqual(s1.at(i), s1.c_str()[i]);
			}
		}
		TEST_METHOD(AtThrowsOutOfRange)
		{
			MyString s1Copy = s1;
			Assert::ExpectException<std::out_of_range>([s1Copy]() {
				s1Copy.at(-1);
			});
			Assert::ExpectException<std::out_of_range>([s1Copy]() {
				s1Copy.at(s1Copy.length());
				});
			Assert::ExpectException<std::out_of_range>([s1Copy]() {
				s1Copy.at(s1Copy.length() + 1);
				});
		}
		TEST_METHOD(IndexationReturnsCorrectly)
		{
			for (size_t i = 0; i < s1.length(); i++)
			{
				Assert::AreEqual(s1[i], s1.c_str()[i]);
			}
		}
		TEST_METHOD(FrontReturnsCorrectly)
		{
			Assert::AreEqual('t', s1.front());
		}
		TEST_METHOD(FrontThrows)
		{
			MyString str;
			Assert::ExpectException<std::logic_error>([str]() {
				str.front();
				});
		}
		TEST_METHOD(BackReturnsCorrectly)
		{
			Assert::AreEqual('t', s1.back());
		}
		TEST_METHOD(BackThrows)
		{
			MyString str;
			Assert::ExpectException<std::logic_error>([str]() {
				str.back();
				});
		}
		TEST_METHOD(ReturnsLengthCorrectly)
		{
			Assert::AreEqual((size_t)4, s1.length());

			MyString str;
			Assert::AreEqual((size_t)0, str.length());
		}
		TEST_METHOD(ReturnsCapacityCorrectly)
		{
			Assert::AreEqual((size_t)8, s1.capacity());

			MyString str;
			Assert::AreEqual((size_t)8, str.capacity());

			MyString longText = "long text that is used for the purpose of texting";
			Assert::AreEqual((size_t)64, longText.capacity());
		}
		TEST_METHOD(ShrinksCorrectly)
		{
			s1.shrink_to_fit();
			Assert::AreEqual((size_t)5, s1.capacity());

			MyString str;
			str.shrink_to_fit();
			Assert::AreEqual((size_t)1, str.capacity());

			MyString longText = "long text that is used for the purpose of texting";
			longText.shrink_to_fit();
			Assert::AreEqual((size_t)50, longText.capacity());
		}
		TEST_METHOD(ClearsCorrectly)
		{
			s1.clear();
			Assert::AreEqual((size_t)0, s1.length());
		}
		TEST_METHOD(InsertsCorrectly)
		{
			MyString str = "abcdefgh";
			str.insert('t', 0);
			Assert::IsTrue("tabcdefgh" == str);

			MyString str1 = "abcdefgh";
			str1.insert('t', str1.length());
			Assert::IsTrue("abcdefght" == str1);
			
			MyString str2 = "abcdefgh";
			str2.insert('t', 3);
			Assert::IsTrue("abctdefgh" == str2);

			MyString str3 = "abcdefgh";
			str3.insert_range("test", 0);
			Assert::IsTrue("testabcdefgh" == str3);

			MyString str4 = "abcdefgh";
			str4.insert_range("test", 3);
			Assert::IsTrue("abctestdefgh" == str4);
		}
		TEST_METHOD(ReplacesCorrectly)
		{
			s1.replace("c", 0);
			Assert::IsTrue("cest" == s1);
		}
		TEST_METHOD(PushesCorrectly)
		{
			s1.push_back('a');
			Assert::IsTrue("testa" == s1);
		}
		TEST_METHOD(PopsCorrectly)
		{
			s1.pop_back();
			Assert::IsTrue("tes" == s1);
			Assert::AreEqual((size_t)3, s1.length());
			s1.pop_back();
			Assert::IsTrue("te" == s1);
			Assert::AreEqual((size_t)2, s1.length());
			s1.pop_back();
			Assert::IsTrue("t" == s1);
			Assert::AreEqual((size_t)1, s1.length());
			s1.pop_back();
			Assert::IsTrue("" == s1);
			Assert::AreEqual((size_t)0, s1.length());
		}
		TEST_METHOD(PopThrows)
		{
			MyString str;
			Assert::ExpectException<std::logic_error>([&str]() {
				str.pop_back();
				});
		}
		TEST_METHOD(AppendsCorrectly)
		{
			s1.append('c', 10);
			Assert::IsTrue("testcccccccccc" == s1);

			MyString str = "test";
			str.append('c');
			Assert::IsTrue("testc" == str);

			MyString str1 = "test";
			str1.append("example", 2);
			Assert::IsTrue("testexampleexample" == str1);
		}
		TEST_METHOD(ThrowsOnAppend)
		{
			MyString str = "test";
			Assert::ExpectException<std::invalid_argument>([&str]() {
				str.append(nullptr, 2);
				});
		}
		TEST_METHOD(PrependsCorrectly)
		{
			s1.prepend('c', 10);
			Assert::IsTrue("cccccccccctest" == s1);

			MyString str = "test";
			str.prepend('c');
			Assert::IsTrue("ctest" == str);

			MyString str1 = "test";
			str1.prepend("example", 2);
			Assert::IsTrue("exampleexampletest" == str1);
		}
		TEST_METHOD(ThrowsOnPrepend)
		{
			MyString str = "test";
			Assert::ExpectException<std::invalid_argument>([&str]() {
				str.prepend(nullptr, 2);
				});
		}
		TEST_METHOD(TakesWhileCondition)
		{
			MyString str = "<html id=\"examples\"></html>";
			Assert::IsTrue(str.takeWhile([](char c) {return c != '\"';}) == "<html id=");
		}
		TEST_METHOD(SkipsWhileCondition)
		{
			MyString str = "<html id=\"examples\"></html>";
			Assert::IsTrue(str.skipWhile([](char c) {return c != '\"';}) == "\"examples\"></html>");
		}
		TEST_METHOD(TrimsCorrectly)
		{
			MyString str = "\v\v\n\r\t<html id=\"examples\"></html>\t\t\n\t\n\r\v";
			Assert::IsTrue(str.trim() == "<html id=\"examples\"></html>");
		}
		TEST_METHOD(TakesSubstringCorrectly)
		{
			MyString str = "test example test";
			Assert::IsTrue(str.substr(0) == "test example test");
			Assert::IsTrue(str.substr(0, 0) == "");
			Assert::IsTrue(str.substr(0, 1) == "t");
			Assert::IsTrue(str.substr(4, 5) == " exam");
		}
		TEST_METHOD(ThrowsOnSubstring)
		{
			MyString str = "test";
			Assert::ExpectException<std::logic_error>([&str]()
				{
					str.substr(3, 10);
				});
		}
		TEST_METHOD(ReversesCorrectly)
		{
			MyString str = "test";
			Assert::IsTrue(str.reverse() == "tset");
			MyString str1;
			Assert::IsTrue("" == str1);
		}
		TEST_METHOD(SplitsCorrectly)
		{
			MyString str = "test example test";
			MyVector<MyString> splitted = str.split();
			Assert::IsTrue(splitted[0] == "test");
			Assert::IsTrue(splitted[1] == "example");
			Assert::IsTrue(splitted[2] == "test");

			MyString str1;
			MyVector<MyString> splitted1 = str1.split();
			Assert::IsTrue(splitted1.empty());
		}
		TEST_METHOD(FindsSubstringCorrectly)
		{
			MyString str = "test example test";
			Assert::AreEqual(str.find(" "), 4);
			Assert::AreEqual(str.rfind(" "), 12);
			Assert::AreEqual(str.find("test"), 0);
			Assert::AreEqual(str.rfind("test"), 13);
		}
		TEST_METHOD(StartsWithCorrectly)
		{
			MyString str = "test example test";
			Assert::IsTrue(str.starts_with("test"));
			Assert::IsTrue(str.starts_with(""));
			Assert::IsTrue(str.starts_with("test example test"));
			Assert::IsTrue(!str.starts_with("test example test "));
		}
		TEST_METHOD(EndsWithCorrectly)
		{
			MyString str = "test example test";
			Assert::IsTrue(str.ends_with("test"));
			Assert::IsTrue(str.ends_with(""));
			Assert::IsTrue(str.ends_with("test example test"));
			Assert::IsTrue(!str.ends_with("test example test "));
		}
		TEST_METHOD(ComparesCorrectly)
		{
			Assert::IsTrue("abc" < "s");
			Assert::IsTrue("abc" == "abc");
			Assert::IsTrue("abc" != "ab");
			Assert::IsTrue("abc" <= "abc");
			Assert::IsTrue("abc" >= "abc");
			Assert::IsTrue("z" > "abc");
		}
	};
}
