
#include "strformat.h"

void test_(char const *text, std::string const &result, char const *answer1, char const *answer2, bool show);

#define TEST(Q, A1, A2) test_(#Q, (Q).str(), A1, A2, show)

void test(bool show)
{
	// f

	TEST(strformat("%.*f").f(0, -1, 0)
		 , "0", nullptr);
	TEST(strformat("%.*f").f(0.000000012345678901234567890123456789, -1, 0)
		 , "0", nullptr);
	TEST(strformat("%.*f").f(123.0, -1, 0)
		 , "123", nullptr);
	TEST(strformat("%.*f").f(123.4567890123456789, -1, 0)
		 , "123", nullptr);
	TEST(strformat("%.*f").f(12345678901234567890.0, -1, 0)
		 , "12345678901234567000", "12345678901234566000");

	TEST(strformat("%.*f").f(0, -1, 1)
		 , "0.0", nullptr);
	TEST(strformat("%.*f").f(0.000000012345678901234567890123456789, -1, 1)
		 , "0.0", nullptr);
	TEST(strformat("%.*f").f(123.0, -1, 1)
		 , "123.0", nullptr);
	TEST(strformat("%.*f").f(123.4567890123456789, -1, 1)
		 , "123.5", nullptr);
	TEST(strformat("%.*f").f(12345678901234567890.0, -1, 1)
		 , "12345678901234567000.0", "12345678901234566000.0");

	TEST(strformat("%.*f").f(0, -1, 2)
		 , "0.00", nullptr);
	TEST(strformat("%.*f").f(0.000000012345678901234567890123456789, -1, 2)
		 , "0.00", nullptr);
	TEST(strformat("%.*f").f(123.0, -1, 2)
		 , "123.00", nullptr);
	TEST(strformat("%.*f").f(123.4567890123456789, -1, 2)
		 , "123.46", nullptr);
	TEST(strformat("%.*f").f(12345678901234567890.0, -1, 2)
		 , "12345678901234567000.00", "12345678901234566000.00");

	TEST(strformat("%.*f").f(0, -1, 5)
		 , "0.00000", nullptr);
	TEST(strformat("%.*f").f(0.000000012345678901234567890123456789, -1, 5)
		 , "0.00000", nullptr);
	TEST(strformat("%.*f").f(123.0, -1, 5)
		 , "123.00000", nullptr);
	TEST(strformat("%.*f").f(123.4567890123456789, -1, 5)
		 , "123.45679", nullptr);
	TEST(strformat("%.*f").f(12345678901234567890.0, -1, 5)
		 , "12345678901234567000.00000", "12345678901234566000.00000");

	TEST(strformat("%.*f").f(0, -1, 10)
		 , "0.0000000000", nullptr);
	TEST(strformat("%.*f").f(0.000000012345678901234567890123456789, -1, 10)
		 , "0.0000000123", nullptr);
	TEST(strformat("%.*f").f(123.0, -1, 10)
		 , "123.0000000000", nullptr);
	TEST(strformat("%.*f").f(123.4567890123456789, -1, 10)
		 , "123.4567890123", nullptr);
	TEST(strformat("%.*f").f(12345678901234567890.0, -1, 10)
		 , "12345678901234567000.0000000000", "12345678901234566000.0000000000");

	TEST(strformat("%.*f").f(0, -1, 15)
		 , "0.000000000000000", nullptr);
	TEST(strformat("%.*f").f(0.000000012345678901234567890123456789, -1, 15)
		 , "0.000000012345678", nullptr);
	TEST(strformat("%.*f").f(123.0, -1, 15)
		 , "123.000000000000000", nullptr);
	TEST(strformat("%.*f").f(123.4567890123456789, -1, 15)
		 , "123.456789012345670", "123.456789012345680");
	TEST(strformat("%.*f").f(12345678901234567890.0, -1, 15)
		 , "12345678901234567000.000000000000000", "12345678901234566000.000000000000000");

	TEST(strformat("%.*f").f(0, -1, 30)
		 , "0.000000000000000000000000000000", nullptr);
	TEST(strformat("%.*f").f(0.000000012345678901234567890123456789, -1, 30)
		 , "0.000000012345678901234567000000", "0.000000012345678901234568000000");
	TEST(strformat("%.*f").f(123.0, -1, 30)
		 , "123.000000000000000000000000000000", nullptr);
	TEST(strformat("%.*f").f(123.4567890123456789, -1, 30)
		 , "123.456789012345670000000000000000", "123.456789012345680000000000000000");
	TEST(strformat("%.*f").f(12345678901234567890.0, -1, 30)
		 , "12345678901234567000.000000000000000000000000000000", "12345678901234566000.000000000000000000000000000000");

	TEST(strformat("(%f)").f(123.456)
		 , "(123.456000)", nullptr);
	TEST(strformat("(%0f)").f(123.456)
		 , "(123.456000)", nullptr);
	TEST(strformat("(%-f)").f(123.456)
		 , "(123.456000)", nullptr);
	TEST(strformat("(%+0f)").f(123.456)
		 , "(+123.456000)", nullptr);

	TEST(strformat("(%15.4f)").f(123.456)
		 , "(       123.4560)", nullptr);
	TEST(strformat("(%015.4f)").f(123.456)
		 , "(0000000123.4560)", nullptr);
	TEST(strformat("(%-15.4f)").f(123.456)
		 , "(123.4560       )", nullptr);
	TEST(strformat("(%+015.4f)").f(123.456)
		 , "(+000000123.4560)", nullptr);

	TEST(strformat("(%*.4f)").f(123.456, 15)
		 , "(       123.4560)", nullptr);
	TEST(strformat("(%0*.4f)").f(123.456, 15)
		 , "(0000000123.4560)", nullptr);
	TEST(strformat("(%-*.4f)").f(123.456, 15)
		 , "(123.4560       )", nullptr);
	TEST(strformat("(%+0*.4f)").f(123.456, 15)
		 , "(+000000123.4560)", nullptr);

	TEST(strformat("(%.*f)").f(123.456, -1, 4)
		 , "(123.4560)", nullptr);
	TEST(strformat("(%0.*f)").f(123.456, -1, 4)
		 , "(123.4560)", nullptr);
	TEST(strformat("(%-.*f)").f(123.456, -1, 4)
		 , "(123.4560)", nullptr);
	TEST(strformat("(%+0.*f)").f(123.456, -1, 4)
		 , "(+123.4560)", nullptr);

	TEST(strformat("(%*.*f)").f(123.456, 15, 4)
		 , "(       123.4560)", nullptr);
	TEST(strformat("(%0*.*f)").f(123.456, 15, 4)
		 , "(0000000123.4560)", nullptr);
	TEST(strformat("(%-*.*f)").f(123.456, 15, 4)
		 , "(123.4560       )", nullptr);
	TEST(strformat("(%+0*.*f)").f(123.456, 15, 4)
		 , "(+000000123.4560)", nullptr);

	// c

	TEST(strformat("(%c)").c(65)
		 , "(A)", nullptr);
	TEST(strformat("(%10c)").c(65)
		 , "(         A)", nullptr);
	TEST(strformat("(%010c)").c(65)
		 , "(000000000A)", nullptr);
	TEST(strformat("(%-10c)").c(65)
		 , "(A         )", nullptr);
	TEST(strformat("(%*c)").c(65, 10)
		 , "(         A)", nullptr);
	TEST(strformat("(%0*c)").c(65, 10)
		 , "(000000000A)", nullptr);
	TEST(strformat("(%-*c)").c(65, 10)
		 , "(A         )", nullptr);
	TEST(strformat("%%%c%c%c%%").c(65).c(66).c(67)
		 , "%ABC%", nullptr);

	// s

	TEST(strformat("(%s)").s("hoge")
		 , "(hoge)", nullptr);
	TEST(strformat("(%10s)").s("hoge")
		 , "(      hoge)", nullptr);
	TEST(strformat("(%-10s)").s("hoge")
		 , "(hoge      )", nullptr);
	TEST(strformat("(%010s)").s("hoge")
		 , "(000000hoge)", nullptr);
}

