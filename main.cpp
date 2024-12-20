
#include "strformat.h"
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#endif


class ElapsedTimer {
private:
	std::chrono::system_clock::time_point start_;
public:
	void start()
	{
		start_ = std::chrono::system_clock::now();
	}
	unsigned long elapsed() const
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_).count();
	}
};

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

void benchmark()
{
	ElapsedTimer t;
	t.start();
	for (int i = 0; i < 10000; i++) {
		test();
	}
	printf("%lldms\n", (unsigned long long)t.elapsed());
}

int main()
{
#if 1
	test();
	print_result();
#elif 1
	benchmark();
#else
	std::string s;
	s = strformat()(13.42).str();
	puts(s.c_str());
#endif
	return 0;
}
