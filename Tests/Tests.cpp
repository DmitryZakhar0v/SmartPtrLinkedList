#include "pch.h"
#include "CppUnitTest.h"
#include "../LinkedListSmartPtr/List.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(ListTests)
	{
	public:
		TEST_METHOD(ToString_ValidData_Success)
		{
			//arrange
			List list{ 1,2,3,4,5,6 };

			//assert
			Assert::IsTrue(list.to_string() == "[ 1 2 3 4 5 6 ]");
		}

		TEST_METHOD(EqualOperator_ValidData_Success)
		{
			//arrange
			List list_1{ 1,2,3,4,5,6 };
			List list_2{ 1,2,3,4,5,6 };
			
			//assert
			Assert::IsTrue(list_1 == list_2);
		}

		TEST_METHOD(NotEqualOperator_ValidData_Success)
		{
			//arrange
			List list_1{ 1,2,3,4,5,6 };
			List list_2{ 3,5,6,75,6 };

			//assert
			Assert::IsTrue(list_1 != list_2);
		}

		TEST_METHOD(Push_ValidData_Success)
		{
			//arrange
			List list{ 1,2,3,4,5 };
			List expected{ 6,1,2,3,4,5 };

			//act
			list.push(6);
			
			//assert
			Assert::IsTrue(list == expected);
		}

		TEST_METHOD(Pop_ValidData_Success)
		{
			//arrange
			List list{ 1,2,3,4,5 };
			List expected{ 2,3,4,5 };

			//act
			list.pop();
			
			//assert
			Assert::IsTrue(list == expected);
		}

		TEST_METHOD(HasElements_ValidData_Success)
		{
			//arrange
			List list{ 1,2,3,4,5 };

			//assert
			Assert::IsTrue(list.has_elements());
		}

		TEST_METHOD(OutputOperator_ValidData_Success)
		{
			//arrange
			std::stringstream sstring;
			List list = List({ 1,2,3,4 });

			//act
			sstring << list;
			
			//assert
			Assert::AreEqual(sstring.str(), list.to_string());
		}

		TEST_METHOD(CopyOperator_ValidData_Success)
		{
			//arrange
			List list_1{ 1,2,3,4,5 };
			List list_2{ 1,5,10,15 };

			//act
			list_1 = list_2;

			//assert
			Assert::IsTrue(list_1 == list_2);
		}

		TEST_METHOD(MoveOperator_ValidData_Success)
		{
			//arrange
			List list_1{ 1,2,3,4,5 };
			List list_2{ 1,5,10,15 };
			List expected{ 1,5,10,15 };

			//act
			list_1 = std::move(list_2);

			//assert
			Assert::IsTrue(list_1 == expected);
		}

		TEST_METHOD(Find_ValidData_Success)
		{
			//arrange
			List list_1{ 1, 2,3,4,5 };

			//assert
			Assert::IsTrue(list_1.find(3));
		}
	};
};