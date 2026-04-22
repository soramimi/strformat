
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
bool report_error = true;

void test_(char const *text, std::string const &result, const char *answer1, const char *answer2, char const *file, int line)
{
	total++;
	if (result == answer1) {
		passed++;
	} else if (answer2 && result == answer2) {
		passed++;
	} else if (report_error) {
		fmt("[fail] %s expected '%s', but returned '%s', %s (%d)\n").s(text).s(answer1).s(result).s(file).d(line).err();
		failed++;
	}
}

void print_result()
{
	fmt("\n" " total: %d\n" "passed: %d\n" "failed: %d\n").d(total).d(passed).d(failed).err();
}

void benchmark()
{
	report_error = false;

	ElapsedTimer t;
	t.start();
	for (int i = 0; i < 10000; i++) {
#if 1
		test();
#elif 0
		fmt("s:%s f:%f d:%d\n")("Hello, world")(123.456)(789).str();
#else
		char tmp[1000];
		sprintf(tmp, "s:%s f:%f d:%d\n", "Hello, world", 123.456, 789);
#endif
	}
	fprintf(stderr, "%lldms\n", (unsigned long long)t.elapsed());
}

int main()
{
	if (0) {
		char *p = setlocale(LC_NUMERIC, "fr_FR.UTF-8");
		if (p) puts(p);
	}

#if 1
	report_error = true;
	test();
	print_result();

	benchmark();


#else
	std::string s;
	s = strformat()(13.42).str();
	puts(s.c_str());
#endif
	return 0;
}
