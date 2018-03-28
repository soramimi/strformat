
#include "strformat.h"
#include <cmath>

void test_(char const *text, std::string const &result, char const *answer1, char const *answer2, bool show);

#define TEST1(Q, A1)     test_(#Q, (Q).str(), A1, nullptr, show)
#define TEST2(Q, A1, A2) test_(#Q, (Q).str(), A1, A2     , show)

void test(bool show)
{
	// operator ()

	TEST1(strformat("(%0*.*f)")(123.456789, 10, 2)
		 , "(0000123.46)");

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
	TEST2(strformat("%.*f").f(12345678901234567890.0, -1, 0)
		 , "12345678901234567000", "12345678901234566000");

	TEST1(strformat("%.*f").f(0.000000012345678901234567890123456789, -1, 1)
		 , "0.0");
	TEST1(strformat("%.*f").f(123.0, -1, 1)
		 , "123.0");
	TEST1(strformat("%.*f").f(123.4567890123456789, -1, 1)
		 , "123.5");
	TEST2(strformat("%.*f").f(12345678901234567890.0, -1, 1)
		 , "12345678901234567000.0", "12345678901234566000.0");

	TEST1(strformat("%.*f").f(0.000000012345678901234567890123456789, -1, 2)
		 , "0.00");
	TEST1(strformat("%.*f").f(123.0, -1, 2)
		 , "123.00");
	TEST1(strformat("%.*f").f(123.4567890123456789, -1, 2)
		 , "123.46");
	TEST2(strformat("%.*f").f(12345678901234567890.0, -1, 2)
		 , "12345678901234567000.00", "12345678901234566000.00");

	TEST1(strformat("%.*f").f(0.000000012345678901234567890123456789, -1, 5)
		 , "0.00000");
	TEST1(strformat("%.*f").f(123.0, -1, 5)
		 , "123.00000");
	TEST1(strformat("%.*f").f(123.4567890123456789, -1, 5)
		 , "123.45679");
	TEST2(strformat("%.*f").f(12345678901234567890.0, -1, 5)
		 , "12345678901234567000.00000", "12345678901234566000.00000");

	TEST1(strformat("%.*f").f(0.000000012345678901234567890123456789, -1, 10)
		 , "0.0000000123");
	TEST1(strformat("%.*f").f(123.0, -1, 10)
		 , "123.0000000000");
	TEST1(strformat("%.*f").f(123.4567890123456789, -1, 10)
		 , "123.4567890123");
	TEST2(strformat("%.*f").f(12345678901234567890.0, -1, 10)
		 , "12345678901234567000.0000000000", "12345678901234566000.0000000000");

	TEST1(strformat("%.*f").f(0.000000012345678901234567890123456789, -1, 15)
		 , "0.000000012345678");
	TEST1(strformat("%.*f").f(123.0, -1, 15)
		 , "123.000000000000000");
	TEST2(strformat("%.*f").f(123.4567890123456789, -1, 15)
		 , "123.456789012345670", "123.456789012345680");
	TEST2(strformat("%.*f").f(12345678901234567890.0, -1, 15)
		 , "12345678901234567000.000000000000000", "12345678901234566000.000000000000000");

	TEST2(strformat("%.*f").f(0.000000012345678901234567890123456789, -1, 30)
		 , "0.000000012345678901234567000000", "0.000000012345678901234568000000");
	TEST1(strformat("%.*f").f(123.0, -1, 30)
		 , "123.000000000000000000000000000000");
	TEST2(strformat("%.*f").f(123.4567890123456789, -1, 30)
		 , "123.456789012345670000000000000000", "123.456789012345680000000000000000");
	TEST2(strformat("%.*f").f(12345678901234567890.0, -1, 30)
		 , "12345678901234567000.000000000000000000000000000000", "12345678901234566000.000000000000000000000000000000");

	TEST1(strformat("(%f)").f(123.456)
		 , "(123.456000)");
	TEST1(strformat("(%0f)").f(123.456)
		 , "(123.456000)");
	TEST1(strformat("(%-f)").f(123.456)
		 , "(123.456000)");
	TEST1(strformat("(%+0f)").f(123.456)
		 , "(+123.456000)");

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

	// f (negative)

	TEST1(strformat("%.*f").f(-0.000000012345678901234567890123456789, -1, 0)
		 , "-0");
	TEST1(strformat("%.*f").f(-123.0, -1, 0)
		 , "-123");
	TEST1(strformat("%.*f").f(-123.4567890123456789, -1, 0)
		 , "-123");
	TEST2(strformat("%.*f").f(-12345678901234567890.0, -1, 0)
		 , "-12345678901234567000", "-12345678901234566000");

	TEST1(strformat("%.*f").f(-0.000000012345678901234567890123456789, -1, 1)
		 , "-0.0");
	TEST1(strformat("%.*f").f(-123.0, -1, 1)
		 , "-123.0");
	TEST1(strformat("%.*f").f(-123.4567890123456789, -1, 1)
		 , "-123.5");
	TEST2(strformat("%.*f").f(-12345678901234567890.0, -1, 1)
		 , "-12345678901234567000.0", "-12345678901234566000.0");

	TEST1(strformat("%.*f").f(-0.000000012345678901234567890123456789, -1, 2)
		 , "-0.00");
	TEST1(strformat("%.*f").f(-123.0, -1, 2)
		 , "-123.00");
	TEST1(strformat("%.*f").f(-123.4567890123456789, -1, 2)
		 , "-123.46");
	TEST2(strformat("%.*f").f(-12345678901234567890.0, -1, 2)
		 , "-12345678901234567000.00", "-12345678901234566000.00");

	TEST1(strformat("%.*f").f(-0.000000012345678901234567890123456789, -1, 5)
		 , "-0.00000");
	TEST1(strformat("%.*f").f(-123.0, -1, 5)
		 , "-123.00000");
	TEST1(strformat("%.*f").f(-123.4567890123456789, -1, 5)
		 , "-123.45679");
	TEST2(strformat("%.*f").f(-12345678901234567890.0, -1, 5)
		 , "-12345678901234567000.00000", "-12345678901234566000.00000");

	TEST1(strformat("%.*f").f(-0.000000012345678901234567890123456789, -1, 10)
		 , "-0.0000000123");
	TEST1(strformat("%.*f").f(-123.0, -1, 10)
		 , "-123.0000000000");
	TEST1(strformat("%.*f").f(-123.4567890123456789, -1, 10)
		 , "-123.4567890123");
	TEST2(strformat("%.*f").f(-12345678901234567890.0, -1, 10)
		 , "-12345678901234567000.0000000000", "-12345678901234566000.0000000000");

	TEST1(strformat("%.*f").f(-0.000000012345678901234567890123456789, -1, 15)
		 , "-0.000000012345678");
	TEST1(strformat("%.*f").f(-123.0, -1, 15)
		 , "-123.000000000000000");
	TEST2(strformat("%.*f").f(-123.4567890123456789, -1, 15)
		 , "-123.456789012345670", "-123.456789012345680");
	TEST2(strformat("%.*f").f(-12345678901234567890.0, -1, 15)
		 , "-12345678901234567000.000000000000000", "-12345678901234566000.000000000000000");

	TEST2(strformat("%.*f").f(-0.000000012345678901234567890123456789, -1, 30)
		 , "-0.000000012345678901234567000000", "-0.000000012345678901234568000000");
	TEST1(strformat("%.*f").f(-123.0, -1, 30)
		 , "-123.000000000000000000000000000000");
	TEST2(strformat("%.*f").f(-123.4567890123456789, -1, 30)
		 , "-123.456789012345670000000000000000", "-123.456789012345680000000000000000");
	TEST2(strformat("%.*f").f(-12345678901234567890.0, -1, 30)
		 , "-12345678901234567000.000000000000000000000000000000", "-12345678901234566000.000000000000000000000000000000");

	TEST1(strformat("(%f)").f(-123.456)
		 , "(-123.456000)");
	TEST1(strformat("(%0f)").f(-123.456)
		 , "(-123.456000)");
	TEST1(strformat("(%-f)").f(-123.456)
		 , "(-123.456000)");
	TEST1(strformat("(%+0f)").f(-123.456)
		 , "(-123.456000)");

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
	TEST1(strformat("(%c)").s("0x32")
		 , "(2)");

}

