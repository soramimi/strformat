
#include "strformat.h"
#include <cmath>

void test_(char const *text, std::string const &result, char const *answer1, char const *answer2);

#define TEST1(Q, A1)         test_(#Q, (Q).str(), A1, nullptr)
#define TEST2(Q, A1, A2)     test_(#Q, (Q).str(), A1, A2     )

void test()
{
	// operator ()

	TEST1(strformat("(%0*.*f)")(123.456789, 10, 2)
		 , "(0000123.46)");

	// d

	TEST1(strformat("%d").d(0)
		 , "0");
	TEST1(strformat("%d").d(123)
		 , "123");
	TEST1(strformat("%d").d(-123)
		 , "-123");
	TEST1(strformat("%d").d(0x7fffffff)
		 , "2147483647");
	TEST1(strformat("%d").d(0x80000000)
		 , "-2147483648");
	TEST1(strformat("%d").d(0xffffffff)
		 , "-1");
	TEST1(strformat("%12d").d(0)
		 , "           0");
	TEST1(strformat("%12d").d(123)
		 , "         123");
	TEST1(strformat("%12d").d(-123)
		 , "        -123");
	TEST1(strformat("%12d").d(0x7fffffff)
		 , "  2147483647");
	TEST1(strformat("%12d").d(0x80000000)
		 , " -2147483648");
	TEST1(strformat("%12d").d(0xffffffff)
		 , "          -1");
	TEST1(strformat("%012d").d(0)
		 , "000000000000");
	TEST1(strformat("%012d").d(123)
		 , "000000000123");
	TEST1(strformat("%012d").d(-123)
		 , "-00000000123");
	TEST1(strformat("%012d").d(0x7fffffff)
		 , "002147483647");
	TEST1(strformat("%012d").d(0x80000000)
		 , "-02147483648");
	TEST1(strformat("%012d").d(0xffffffff)
		 , "-00000000001");

	// u

	TEST1(strformat("%u").u(0)
		 , "0");
	TEST1(strformat("%u").u(123)
		 , "123");
	TEST1(strformat("%u").u(-123)
		 , "4294967173");
	TEST1(strformat("%u").u(0x7fffffff)
		 , "2147483647");
	TEST1(strformat("%u").u(0x80000000)
		 , "2147483648");
	TEST1(strformat("%u").u(0xffffffff)
		 , "4294967295");
	TEST1(strformat("%12u").u(0)
		 , "           0");
	TEST1(strformat("%12u").u(123)
		 , "         123");
	TEST1(strformat("%12u").u(-123)
		 , "  4294967173");
	TEST1(strformat("%12u").u(0x7fffffff)
		 , "  2147483647");
	TEST1(strformat("%12u").u(0x80000000)
		 , "  2147483648");
	TEST1(strformat("%12u").u(0xffffffff)
		 , "  4294967295");
	TEST1(strformat("%012u").u(0)
		 , "000000000000");
	TEST1(strformat("%012u").u(123)
		 , "000000000123");
	TEST1(strformat("%012u").u(-123)
		 , "004294967173");
	TEST1(strformat("%012u").u(0x7fffffff)
		 , "002147483647");
	TEST1(strformat("%012u").u(0x80000000)
		 , "002147483648");
	TEST1(strformat("%012u").u(0xffffffff)
		 , "004294967295");

	// f (zero)

	TEST1(strformat("%.*f").f(0, -1, 0)
		 , "0");
	TEST1(strformat("%.*f").f(0, -1, 1)
		 , "0.0");
	TEST1(strformat("%.*f").f(0, -1, 2)
		 , "0.00");
	TEST1(strformat("%.*f").f(0, -1, 5)
		 , "0.00000");
	TEST1(strformat("%.*f").f(0, -1, 10)
		 , "0.0000000000");
	TEST1(strformat("%.*f").f(0, -1, 15)
		 , "0.000000000000000");
	TEST1(strformat("%.*f").f(0, -1, 30)
		 , "0.000000000000000000000000000000");
	TEST1(strformat("(%10.3f)").f(0)
		 , "(     0.000)");
	TEST1(strformat("(%-10.3f)").f(0)
		 , "(0.000     )");
	TEST1(strformat("(%+10.3f)").f(0)
		 , "(    +0.000)");
	TEST1(strformat("(%+-10.3f)").f(0)
		 , "(+0.000    )");
	TEST1(strformat("(%010.3f)").f(0)
		 , "(000000.000)");
	TEST1(strformat("(%+010.3f)").f(0)
		 , "(+00000.000)");

	// f (positive)

	TEST1(strformat("%.*f").f(0.000000012345678901234567890123456789, -1, 0)
		 , "0");
	TEST1(strformat("%.*f").f(123.0, -1, 0)
		 , "123");
	TEST1(strformat("%.*f").f(123.4567890123456789, -1, 0)
		 , "123");
	TEST1(strformat("%.*f").f(12345678901234567890.0, -1, 0)
		 , "12345678901234567000");

	TEST1(strformat("%.*f").f(0.000000012345678901234567890123456789, -1, 1)
		 , "0.0");
	TEST1(strformat("%.*f").f(123.0, -1, 1)
		 , "123.0");
	TEST1(strformat("%.*f").f(123.4567890123456789, -1, 1)
		 , "123.5");
	TEST1(strformat("%.*f").f(12345678901234567890.0, -1, 1)
		 , "12345678901234567000.0");

	TEST1(strformat("%.*f").f(0.000000012345678901234567890123456789, -1, 2)
		 , "0.00");
	TEST1(strformat("%.*f").f(123.0, -1, 2)
		 , "123.00");
	TEST1(strformat("%.*f").f(123.4567890123456789, -1, 2)
		 , "123.46");
	TEST1(strformat("%.*f").f(12345678901234567890.0, -1, 2)
		 , "12345678901234567000.00");

	TEST1(strformat("%.*f").f(0.000000012345678901234567890123456789, -1, 5)
		 , "0.00000");
	TEST1(strformat("%.*f").f(123.0, -1, 5)
		 , "123.00000");
	TEST1(strformat("%.*f").f(123.4567890123456789, -1, 5)
		 , "123.45679");
	TEST1(strformat("%.*f").f(12345678901234567890.0, -1, 5)
		 , "12345678901234567000.00000");

	TEST1(strformat("%.*f").f(0.000000012345678901234567890123456789, -1, 10)
		 , "0.0000000123");
	TEST1(strformat("%.*f").f(123.0, -1, 10)
		 , "123.0000000000");
	TEST1(strformat("%.*f").f(123.4567890123456789, -1, 10)
		 , "123.4567890123");
	TEST1(strformat("%.*f").f(12345678901234567890.0, -1, 10)
		 , "12345678901234567000.0000000000");

	TEST1(strformat("%.*f").f(0.000000012345678901234567890123456789, -1, 15)
		 , "0.000000012345679");
	TEST1(strformat("%.*f").f(123.0, -1, 15)
		 , "123.000000000000000");
	TEST1(strformat("%.*f").f(123.4567890123456789, -1, 15)
		 , "123.456789012345600");
	TEST1(strformat("%.*f").f(12345678901234567890.0, -1, 15)
		 , "12345678901234567000.000000000000000");

	TEST1(strformat("%.*f").f(0.000000012345678901234567890123456789, -1, 30)
		 , "0.000000012345678901234560000000");
	TEST1(strformat("%.*f").f(123.0, -1, 30)
		 , "123.000000000000000000000000000000");
	TEST1(strformat("%.*f").f(123.4567890123456789, -1, 30)
		 , "123.456789012345600000000000000000");
	TEST1(strformat("%.*f").f(12345678901234567890.0, -1, 30)
		 , "12345678901234567000.000000000000000000000000000000");


	TEST1(strformat("(%f)").f(123.456)
		 , "(123.456000)");
	TEST1(strformat("(%0f)").f(123.456)
		 , "(123.456000)");
	TEST1(strformat("(%-f)").f(123.456)
		 , "(123.456000)");
	TEST1(strformat("(%+0f)").f(123.456)
		 , "(+123.456000)");
	TEST1(strformat("(%f)").f(1.23456789)
		 , "(1.234568)");
	TEST1(strformat("(%+f)").f(1.23456789)
		 , "(+1.234568)");

	TEST1(strformat("(%15.4f)").f(123.456)
		 , "(       123.4560)");
	TEST1(strformat("(%015.4f)").f(123.456)
		 , "(0000000123.4560)");
	TEST1(strformat("(%-15.4f)").f(123.456)
		 , "(123.4560       )");
	TEST1(strformat("(%+015.4f)").f(123.456)
		 , "(+000000123.4560)");

	TEST1(strformat("(%*.4f)").f(123.456, 15)
		 , "(       123.4560)");
	TEST1(strformat("(%0*.4f)").f(123.456, 15)
		 , "(0000000123.4560)");
	TEST1(strformat("(%-*.4f)").f(123.456, 15)
		 , "(123.4560       )");
	TEST1(strformat("(%+0*.4f)").f(123.456, 15)
		 , "(+000000123.4560)");

	TEST1(strformat("(%.*f)").f(123.456, -1, 4)
		 , "(123.4560)");
	TEST1(strformat("(%0.*f)").f(123.456, -1, 4)
		 , "(123.4560)");
	TEST1(strformat("(%-.*f)").f(123.456, -1, 4)
		 , "(123.4560)");
	TEST1(strformat("(%+0.*f)").f(123.456, -1, 4)
		 , "(+123.4560)");

	TEST1(strformat("(%*.*f)").f(123.456, 15, 4)
		 , "(       123.4560)");
	TEST1(strformat("(%0*.*f)").f(123.456, 15, 4)
		 , "(0000000123.4560)");
	TEST1(strformat("(%-*.*f)").f(123.456, 15, 4)
		 , "(123.4560       )");
	TEST1(strformat("(%+0*.*f)").f(123.456, 15, 4)
		 , "(+000000123.4560)");

	TEST1(strformat("%.*f").f(0.9, -1, 0)
		 , "1");
	TEST1(strformat("%.*f").f(9.9, -1, 0)
		 , "10");
	TEST1(strformat("%.*f").f(9.99, -1, 1)
		 , "10.0");

	// f (negative)

	TEST1(strformat("%.*f").f(-0.000000012345678901234567890123456789, -1, 0)
		 , "-0");
	TEST1(strformat("%.*f").f(-123.0, -1, 0)
		 , "-123");
	TEST1(strformat("%.*f").f(-123.4567890123456789, -1, 0)
		 , "-123");
	TEST1(strformat("%.*f").f(-12345678901234567890.0, -1, 0)
		 , "-12345678901234567000");

	TEST1(strformat("%.*f").f(-0.000000012345678901234567890123456789, -1, 1)
		 , "-0.0");
	TEST1(strformat("%.*f").f(-123.0, -1, 1)
		 , "-123.0");
	TEST1(strformat("%.*f").f(-123.4567890123456789, -1, 1)
		 , "-123.5");
	TEST1(strformat("%.*f").f(-12345678901234567890.0, -1, 1)
		 , "-12345678901234567000.0");

	TEST1(strformat("%.*f").f(-0.000000012345678901234567890123456789, -1, 2)
		 , "-0.00");
	TEST1(strformat("%.*f").f(-123.0, -1, 2)
		 , "-123.00");
	TEST1(strformat("%.*f").f(-123.4567890123456789, -1, 2)
		 , "-123.46");
	TEST1(strformat("%.*f").f(-12345678901234567890.0, -1, 2)
		 , "-12345678901234567000.00");

	TEST1(strformat("%.*f").f(-0.000000012345678901234567890123456789, -1, 5)
		 , "-0.00000");
	TEST1(strformat("%.*f").f(-123.0, -1, 5)
		 , "-123.00000");
	TEST1(strformat("%.*f").f(-123.4567890123456789, -1, 5)
		 , "-123.45679");
	TEST1(strformat("%.*f").f(-12345678901234567890.0, -1, 5)
		 , "-12345678901234567000.00000");

	TEST1(strformat("%.*f").f(-0.000000012345678901234567890123456789, -1, 10)
		 , "-0.0000000123");
	TEST1(strformat("%.*f").f(-123.0, -1, 10)
		 , "-123.0000000000");
	TEST1(strformat("%.*f").f(-123.4567890123456789, -1, 10)
		 , "-123.4567890123");
	TEST1(strformat("%.*f").f(-12345678901234567890.0, -1, 10)
		 , "-12345678901234567000.0000000000");

	TEST1(strformat("%.*f").f(-0.000000012345678901234567890123456789, -1, 15)
		 , "-0.000000012345679");
	TEST1(strformat("%.*f").f(-123.0, -1, 15)
		 , "-123.000000000000000");
	TEST1(strformat("%.*f").f(-123.4567890123456789, -1, 15)
		 , "-123.456789012345600");
	TEST1(strformat("%.*f").f(-12345678901234567890.0, -1, 15)
		 , "-12345678901234567000.000000000000000");

	TEST1(strformat("%.*f").f(-0.000000012345678901234567890123456789, -1, 30)
		 , "-0.000000012345678901234560000000");
	TEST1(strformat("%.*f").f(-123.0, -1, 30)
		 , "-123.000000000000000000000000000000");
	TEST1(strformat("%.*f").f(-123.4567890123456789, -1, 30)
		 , "-123.456789012345600000000000000000");
	TEST1(strformat("%.*f").f(-12345678901234567890.0, -1, 30)
		 , "-12345678901234567000.000000000000000000000000000000");

	TEST1(strformat("(%f)").f(-123.456)
		 , "(-123.456000)");
	TEST1(strformat("(%0f)").f(-123.456)
		 , "(-123.456000)");
	TEST1(strformat("(%-f)").f(-123.456)
		 , "(-123.456000)");
	TEST1(strformat("(%+0f)").f(-123.456)
		 , "(-123.456000)");
	TEST1(strformat("(%f)").f(-1.23456789)
		 , "(-1.234568)");
	TEST1(strformat("(%+f)").f(-1.23456789)
		 , "(-1.234568)");

	TEST1(strformat("(%15.4f)").f(-123.456)
		 , "(      -123.4560)");
	TEST1(strformat("(%015.4f)").f(-123.456)
		 , "(-000000123.4560)");
	TEST1(strformat("(%-15.4f)").f(-123.456)
		 , "(-123.4560      )");
	TEST1(strformat("(%+015.4f)").f(-123.456)
		 , "(-000000123.4560)");

	TEST1(strformat("(%*.4f)").f(-123.456, 15)
		 , "(      -123.4560)");
	TEST1(strformat("(%0*.4f)").f(-123.456, 15)
		 , "(-000000123.4560)");
	TEST1(strformat("(%-*.4f)").f(-123.456, 15)
		 , "(-123.4560      )");
	TEST1(strformat("(%+0*.4f)").f(-123.456, 15)
		 , "(-000000123.4560)");

	TEST1(strformat("(%.*f)").f(-123.456, -1, 4)
		 , "(-123.4560)");
	TEST1(strformat("(%0.*f)").f(-123.456, -1, 4)
		 , "(-123.4560)");
	TEST1(strformat("(%-.*f)").f(-123.456, -1, 4)
		 , "(-123.4560)");
	TEST1(strformat("(%+0.*f)").f(-123.456, -1, 4)
		 , "(-123.4560)");

	TEST1(strformat("(%*.*f)").f(-123.456, 15, 4)
		 , "(      -123.4560)");
	TEST1(strformat("(%0*.*f)").f(-123.456, 15, 4)
		 , "(-000000123.4560)");
	TEST1(strformat("(%-*.*f)").f(-123.456, 15, 4)
		 , "(-123.4560      )");
	TEST1(strformat("(%+0*.*f)").f(-123.456, 15, 4)
		 , "(-000000123.4560)");

	TEST1(strformat("%.*f").f(-0.9, -1, 0)
		 , "-1");
	TEST1(strformat("%.*f").f(-9.9, -1, 0)
		 , "-10");
	TEST1(strformat("%.*f").f(-9.99, -1, 1)
		 , "-10.0");

	// f (string)

	TEST1(strformat("(%f)").s("")
		 , "(0.000000)");
	TEST1(strformat("(%f)").s("123")
		 , "(123.000000)");
	TEST1(strformat("(%f)").s("123.")
		 , "(123.000000)");
	TEST1(strformat("(%f)").s(".123")
		 , "(0.123000)");
	TEST1(strformat("(%f)").s("+.123")
		 , "(0.123000)");
	TEST1(strformat("(%f)").s("-.123")
		 , "(-0.123000)");
	TEST1(strformat("(%f)").s("123.456")
		 , "(123.456000)");
	TEST1(strformat("(%+f)").s("123.456")
		 , "(+123.456000)");
	TEST1(strformat("(%+f)").s("+123.456")
		 , "(+123.456000)");
	TEST1(strformat("(%f)").s("-123.456")
		 , "(-123.456000)");
	TEST1(strformat("(%f)").s("123,456")
		 , "(123.000000)");
	TEST1(strformat("(%f)").s("0x50")
		 , "(80.000000)");
	TEST1(strformat("(%+f)").s("0x50")
		 , "(+80.000000)");
	TEST1(strformat("(%+f)").s("+0x50")
		 , "(+80.000000)");
	TEST1(strformat("(%f)").s("-0x50")
		 , "(-80.000000)");
	TEST1(strformat("(%f)").s("0x50.5")
		 , "(80.000000)");
	TEST1(strformat("(%f)").s("0755")
		 , "(493.000000)");
	TEST1(strformat("(%+f)").s("0755")
		 , "(+493.000000)");
	TEST1(strformat("(%f)").s("-0755")
		 , "(-493.000000)");
	TEST1(strformat("(%f)").s("00755")
		 , "(493.000000)");
	TEST1(strformat("(%f)").s(nullptr)
		 , "((null))");

	TEST1(strformat("(%f)").s("1.23456789e2")
		  , "(123.456789)");
	TEST1(strformat("(%f)").s("1.23456789e+2")
		  , "(123.456789)");
	TEST1(strformat("(%f)").s("1.23456789e-2")
		  , "(0.012346)");
	TEST1(strformat("(%f)").s("0.0123456789")
		  , "(0.012346)");

	TEST1(strformat("%s").f(0.9, -1, 0)
		 , "1");
	TEST1(strformat("%s").f(9.9, -1, 0)
		 , "10");
	TEST1(strformat("%s").f(9.99, -1, 1)
		 , "10");

	TEST1(strformat("%s").f(-0.9, -1, 0)
		 , "-1");
	TEST1(strformat("%s").f(-9.9, -1, 0)
		 , "-10");
	TEST1(strformat("%s").f(-9.99, -1, 1)
		 , "-10");

	// f (NAN/INF)

	TEST1(strformat("(%f)").f(sqrt(-1))
		 , "(#NAN)");
	TEST1(strformat("(%10f)").f(sqrt(-1))
		 , "(      #NAN)");
	TEST1(strformat("(%+10f)").f(sqrt(-1))
		 , "(      #NAN)");
	TEST1(strformat("(%-10f)").f(sqrt(-1))
		 , "(#NAN      )");
	TEST1(strformat("(%010f)").f(sqrt(-1))
		 , "(000000#NAN)");

	TEST1(strformat("(%f)").f(log(0))
		 , "(#INF)");
	TEST1(strformat("(%10f)").f(log(0))
		 , "(      #INF)");
	TEST1(strformat("(%+10f)").f(log(0))
		 , "(      #INF)");
	TEST1(strformat("(%-10f)").f(log(0))
		 , "(#INF      )");
	TEST1(strformat("(%010f)").f(log(0))
		 , "(000000#INF)");

	// c

	TEST1(strformat("(%c)").c(65)
		 , "(A)");
	TEST1(strformat("(%10c)").c(65)
		 , "(         A)");
	TEST1(strformat("(%010c)").c(65)
		 , "(000000000A)");
	TEST1(strformat("(%-10c)").c(65)
		 , "(A         )");
	TEST1(strformat("(%*c)").c(65, 10)
		 , "(         A)");
	TEST1(strformat("(%0*c)").c(65, 10)
		 , "(000000000A)");
	TEST1(strformat("(%-*c)").c(65, 10)
		 , "(A         )");
	TEST1(strformat("%%%c%c%c%%").c(65).c(66).c(67)
		 , "%ABC%");

	// s

	TEST1(strformat("(%s)").s("hoge")
		 , "(hoge)");
	TEST1(strformat("(%s)").s(std::string("hoge"))
		 , "(hoge)");
	TEST1(strformat("(%10s)").s("hoge")
		 , "(      hoge)");
	TEST1(strformat("(%-10s)").s("hoge")
		 , "(hoge      )");
	TEST1(strformat("(%010s)").s("hoge")
		 , "(000000hoge)");
	TEST1(strformat("(%s)").s("")
		 , "()");
	TEST1(strformat("(%s)").s(std::string())
		 , "()");
	TEST1(strformat("(%s)").s(nullptr)
		 , "((null))");
	TEST1(strformat("(%10s)").s(nullptr)
		, "(    (null))");
	TEST1(strformat("(%-10s)").s(nullptr)
		, "((null)    )");
	TEST1(strformat("(%010s)").s(nullptr)
		, "(0000(null))");
	TEST1(strformat("(%010s)").s("")
		 , "(0000000000)");
	TEST1(strformat("(%010s)").s(std::string())
		 , "(0000000000)");

	TEST1(strformat("%s%s%s").s("abc").s("def").s("ghi")
		 , "abcdefghi");
	TEST1(strformat("%s%s").s("abc").s("def").s("ghi")
		 , "abcdef");
	TEST1(strformat("%s%s%s%s").s("abc").s("def").s("ghi")
		 , "abcdefghi%s");
	TEST1(strformat("%s%s%s%s%").s("abc").s("def").s("ghi")
		 , "abcdefghi%s%");
	TEST1(strformat("%s%s%s%s%%").s("abc").s("def").s("ghi")
		 , "abcdefghi%s%");
	TEST1(strformat("%s%s%s%s%%%").s("abc").s("def").s("ghi")
		 , "abcdefghi%s%%");
	TEST1(strformat("%%%s%s%s%s%%").s("abc").s("def")
		 , "%abcdef%s%s%");

	TEST1(strformat("%.s").f(0.00123456)
		 , "0.001235");
	TEST1(strformat("%.8s").f(0.00123456)
		 , "0.00123456");
	TEST1(strformat("%s").f(123.0)
		 , "123");
	TEST1(strformat("%s").f(123.456)
		 , "123.456");
	TEST1(strformat("%s").f(-0.00123456)
		 , "-0.001235");
	TEST1(strformat("%.8s").f(-0.00123456)
		 , "-0.00123456");
	TEST1(strformat("%s").f(-123.0)
		 , "-123");
	TEST1(strformat("%s").f(-123.456)
		 , "-123.456");


	// p

	TEST2(strformat("(%p)").p((void *)0)
		 , "(00000000)", "(0000000000000000)");
	TEST2(strformat("(%p)").p((void *)0x0123abcd)
		 , "(0123ABCD)", "(000000000123ABCD)");
	TEST2(strformat("(%20p)").p((void *)0x0123abcd)
		 , "(            0123ABCD)", "(    000000000123ABCD)");
	TEST2(strformat("(%-20p)").p((void *)0x0123abcd)
		 , "(0123ABCD            )", "(000000000123ABCD    )");
	TEST1(strformat("(%020p)").p((void *)0x0123abcd)
		 , "(0000000000000123ABCD)");

	// p (abnormal)

	TEST2(strformat("(%f)").p((void *)0)
		 , "(00000000)", "(0000000000000000)");
	TEST2(strformat("(%f)").p((void *)0x0123abcd)
		 , "(0123ABCD)", "(000000000123ABCD)");
	TEST2(strformat("(%20f)").p((void *)0x0123abcd)
		 , "(            0123ABCD)", "(    000000000123ABCD)");
	TEST2(strformat("(%-20f)").p((void *)0x0123abcd)
		 , "(0123ABCD            )", "(000000000123ABCD    )");
	TEST1(strformat("(%020f)").p((void *)0x0123abcd)
		 , "(0000000000000123ABCD)");
	TEST2(strformat("(%s)").p((void *)0)
		 , "(00000000)", "(0000000000000000)");
	TEST2(strformat("(%s)").p((void *)0x0123abcd)
		 , "(0123ABCD)", "(000000000123ABCD)");
	TEST2(strformat("(%20s)").p((void *)0x0123abcd)
		 , "(            0123ABCD)", "(    000000000123ABCD)");
	TEST2(strformat("(%-20s)").p((void *)0x0123abcd)
		 , "(0123ABCD            )", "(000000000123ABCD    )");
	TEST1(strformat("(%020s)").p((void *)0x0123abcd)
		 , "(0000000000000123ABCD)");


	// c

	TEST1(strformat("(%c)").c('A')
		 , "(A)");
	TEST1(strformat("(%c)").c(48)
		 , "(0)");
	TEST1(strformat("(%c)").s("49")
		 , "(1)");
	TEST1(strformat("(%c)").s("062")
		 , "(2)");
	TEST1(strformat("(%c)").s("0x33")
		 , "(3)");
	TEST1(strformat("(%c)").s("0x4C")
		 , "(L)");
	TEST1(strformat("(%c)").s("0X4d")
		 , "(M)");
	TEST1(strformat("(%c)").s("0116")
		 , "(N)");
}

