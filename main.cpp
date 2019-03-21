
#include "strformat.h"

#ifdef _WIN32
#include <windows.h>
#endif

void test();

int passed = 0;
int failed = 0;
int total = 0;

void test_(char const *text, std::string const &result, const char *answer1, const char *answer2)
{
	total++;

	if (result == answer1) {
		passed++;
	} else if (answer2 && result == answer2) {
		passed++;
	} else {
		strformat("[fail] %s expected '%s'\n , but returned '%s'\n").s(text).s(answer1).s(result).err();
		failed++;
	}
}

void print_result()
{
	strformat("\n" " total: %d\n" "passed: %d\n" "failed: %d\n").d(total).d(passed).d(failed).err();
}

int main()
{
#if 1
	test();
	print_result();
#else
	fprintf(stderr, "%.30f\n", 0.000000012345678901234567890123456789);
	strformat("%.30f\n").f(0.000000012345678901234567890123456789).err();
#endif
	return 0;
}
