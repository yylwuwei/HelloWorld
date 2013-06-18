// GtestStudy.cpp : Defines the entry point for the console application.
//E:\Files_YYL\yylProject\OpenSrc\gtest\gtest-1.6.0\include
//E:\Files_YYL\yylProject\OpenSrc\gtest\gtest-1.6.0\msvc\gtest\Debug\gtestd.lib
//love me little, love me long.

#include "stdafx.h"
#include "gtest/gtest.h"

int Foo(int a, int b)
{
	if (a == 0 || b == 0)
	{
		throw "don't do that";
	}
	int c = a % b;
	if (c == 0)
		return b;
	return Foo(b, c);
}

void Foo2()
{
	int *pInt = 0;
	*pInt = 42 ;
	std::cout << stderr << std::endl;
}

int Add(int a, int b)
{
	return a+b;
}

int Sub(int a, int b)
{
	return a-b;
}

TEST(FooDeathTest, Demo)
{
	EXPECT_DEATH(Foo2(), "error");
}

TEST(FooTest, HandleNoneZeroInput)
{
	EXPECT_EQ(3, Foo(4, 10));
	EXPECT_EQ(6, Foo(30, 18));
	EXPECT_EQ(15, Foo(30, 15));
}

// TEST(BasicTest, AddTestNameYy)
// {
// 	EXPECT_EQ(5, Add(2,3));
// 	EXPECT_EQ(8, Add(3,5));
// }
// 
// TEST(BasicTest, SubTestNameYy)
// {
// 	EXPECT_EQ(5, Sub(6,1));
// 	EXPECT_EQ(6, Sub(9,3));
// }

int _tmain(int argc, _TCHAR* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	//return 0;
}
