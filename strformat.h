#ifndef STRFORMAT_H
#define STRFORMAT_H

#include <stdint.h>
#include <string>
#include <vector>
#include <functional>

class strformat {
public:
	class helper;
	friend class helper;
private:
	struct Part {
		Part *next;
		char *data;
		int size;
	};
	struct PartList {
		Part *head = nullptr;
		Part *last = nullptr;
	};
private:
	std::string text_;
	char const *head_;
	char const *next_;
	PartList list_;
	bool upper_ : 1;
	bool zero_padding_ : 1;
	bool align_left_ : 1;
	bool force_sign_ : 1;
	int width_;
	int precision_;
	int lflag_;

	void clear();
	bool advance();
	Part *format_f(double value, bool trim_fractional_zeros);
	Part *format_c(char c);
	Part *format_o32(int32_t value, int hint);
	Part *format_o64(int64_t value, int hint);
	Part *format_x32(int32_t value, int hint);
	Part *format_x64(int64_t value, int hint);
	Part *format(char c, int hint);
	Part *format(double value, int hint);
	Part *format(int32_t value, int hint);
	Part *format(uint32_t value, int hint);
	Part *format(int64_t value, int hint);
	Part *format(uint64_t value, int hint);
	Part *format(char const *value, int hint);
	Part *format(std::string const &value, int hint);
	Part *format_p(void *val);
	void format(std::function<Part *(int)> callback, int width, int precision);
public:
	strformat(std::string const &text);
	~strformat();

	strformat &reset();
	void destroy();

	strformat &append(std::string const &s);
	strformat &append(char const *s);

	template <typename T> strformat &a(T const &value, int width = -1, int precision = -1)
	{
		format([&](int hint){ return format(value, hint); }, width, precision);
		return *this;
	}
	strformat &f(double value, int width = -1, int precision = -1)
	{
		return a(value, width, precision);
	}
	strformat &c(char value, int width = -1, int precision = -1)
	{
		return a(value, width, precision);
	}
	strformat &d(int32_t value, int width = -1, int precision = -1)
	{
		return a(value, width, precision);
	}
	strformat &ld(int64_t value, int width = -1, int precision = -1)
	{
		return a(value, width, precision);
	}
	strformat &u(uint32_t value, int width = -1, int precision = -1)
	{
		return a(value, width, precision);
	}
	strformat &lu(uint64_t value, int width = -1, int precision = -1)
	{
		return a(value, width, precision);
	}
	strformat &o(int32_t value, int width = -1, int precision = -1)
	{
		format([&](int hint){ return format_o32(value, hint); }, width, precision);
		return *this;
	}
	strformat &lo(int64_t value, int width = -1, int precision = -1)
	{
		format([&](int hint){ return format_o64(value, hint); }, width, precision);
		return *this;
	}
	strformat &x(int32_t value, int width = -1, int precision = -1)
	{
		format([&](int hint){ return format_x32(value, hint); }, width, precision);
		return *this;
	}
	strformat &lx(int64_t value, int width = -1, int precision = -1)
	{
		format([&](int hint){ return format_x64(value, hint); }, width, precision);
		return *this;
	}
	strformat &s(char const *value, int width = -1, int precision = -1)
	{
		return a(value, width, precision);
	}
	strformat &s(std::string const &value, int width = -1, int precision = -1)
	{
		return a(value, width, precision);
	}
	strformat &p(void *value, int width = -1, int precision = -1)
	{
		format([&](int hint){ (void)hint; return format_p(value); }, width, precision);
		return *this;
	}

	template <typename T> strformat &operator () (T const &value, int width = -1, int precision = -1)
	{
		return a(value, width, precision);
	}

	void vec(std::vector<char> *vec);
	void render(std::function<void (char const *ptr, int len)> dst);
	void write_to(FILE *fp);
	void write_to(int fd);
	void out();
	void err();
	std::string str();
};

#endif // STRFORMAT_H
