
#include "strformat.h"

void test();

int passed = 0;
int failed = 0;
int total = 0;

void test_(char const *text, std::string const &result, std::string const &answer)
{
	total++;
	strformat("#%5d %s\n").d(total).s(text).out();

	if (result == answer) {
		strformat("[pass] %s\n").s(answer).out();
		passed++;
	} else {
		strformat("[fail] expected '%s'\n , but returned '%s'\n").s(answer).s(result).out();
		failed++;
	}
}

int main()
{
#if 1
	test();
	strformat("\n" " total: %d\n" "passed: %d\n" "failed: %d\n").d(total).d(passed).d(failed).out();
#else
	char const *fmt = "%.4f\n";
	double val = 123.456;
	printf(fmt, val);
	strformat(fmt).f(val).out();
#endif
	return 0;
}
