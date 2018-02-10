
#include "strformat.h"

#ifdef _WIN32
#include <windows.h>
#endif

void test(bool show);

int passed = 0;
int failed = 0;
int total = 0;

void test_(char const *text, std::string const &result, const char *answer1, const char *answer2, bool show)
{
	total++;
	if (show) strformat("#%5d %s\n").d(total).s(text).out();

	if (result == answer1 || (answer2 && result == answer2)) {
		if (show) strformat("[pass] %s\n").s(answer1).out();
		passed++;
	} else {
		if (show) strformat("[fail] expected '%s'\n , but returned '%s'\n").s(answer1).s(result).out();
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
	test(true);
	print_result();
#elif 0

#ifdef _WIN32
	DWORD ms = GetTickCount();
	for (int i = 0; i < 100000; i++) {
		test(false);
	}
	ms = GetTickCount() - ms;
	print_result();
	strformat("\n%ums\n").u(ms).err();
#endif

#else
	char const *fmt = "(%0*.*f)\n";
	double val = 123.456789;
	printf(fmt, 10, 2, val);
	strformat(fmt)(val, 10, 2).out();
#endif
	return 0;
}
