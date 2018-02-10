#include "strformat.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <cmath>
#include <algorithm>

#ifdef _MSC_VER
#include <io.h>
#else
#include <unistd.h>
#endif

class strformat::helper {
public:
	using Part = strformat::Part;
	using PartList = strformat::PartList;
};

namespace {

using Part = strformat::helper::Part;
using PartList = strformat::helper::PartList;

static char digits_lower[] = "0123456789abcdef";
static char digits_upper[] = "0123456789ABCDEF";

Part *alloc_part(char const *data, int size)
{
	void *v = malloc(sizeof(Part) + size + 1);
	Part *p = (Part *)v;
	p->next = nullptr;
	p->data = (char *)v + sizeof(Part);
	p->size = size;
	memcpy(p->data, data, size);
	p->data[size] = 0;
	return p;
}

Part *alloc_part(char const *begin, char const *end)
{
	return alloc_part(begin, end - begin);
}

Part *alloc_part(char const *str)
{
	return alloc_part(str, strlen(str));
}

Part *alloc_part(std::string const &str)
{
	return alloc_part(str.c_str(), (int)str.size());
}

void free_part(Part **p)
{
	if (p && *p) {
		free(*p);
		*p = nullptr;
	}
}

void add_part(PartList *list, Part *part)
{
	if (part) {
		if (!list->head) {
			list->head = part;
		}
		if (list->last) {
			list->last->next = part;
		}
		list->last = part;
	}
}

void free_list(PartList *list)
{
	Part *p = list->head;
	while (p) {
		Part *next = p->next;
		free_part(&p);
		p = next;
	}
	list->head = nullptr;
	list->last = nullptr;
}

void add_chars(PartList *list, char c, int n)
{
	void *v = malloc(sizeof(Part) + n + 1);
	Part *p = (Part *)v;
	p->next = nullptr;
	p->data = (char *)v + sizeof(Part);
	p->size = n;
	memset(p->data, c, n);
	p->data[n] = 0;
	add_part(list, p);
}

Part *format_double(double val, int precision, bool trim_unnecessary_zeros, bool force_sign)
{
#ifdef _MSC_VER
	switch (_fpclass(val)) {
	case _FPCLASS_PINF:
	case _FPCLASS_NINF:
		return alloc_part("#INF", nullptr);
	case _FPCLASS_SNAN:
	case _FPCLASS_QNAN:
		return alloc_part("#NAN", nullptr);
	case _FPCLASS_PZ:
	case _FPCLASS_NZ:
		val = 0;
		break;
	}
#else
	if (std::isnan(val)) return alloc_part("#NAN");
	if (std::isinf(val)) return alloc_part("#INF");
#endif

	bool sign = val < 0;
	if (sign) val = -val;

	if (precision < 0) precision = 0;

	int pt = (val == 0) ? 0 : (int)floor(log10(val));
	pt++;
	val *= pow(10.0, -pt);
	int length = precision;
	if (pt < 0) {
		if (precision > 0 && precision <= -pt) {
			pt = -precision;
			length = 0;
		}
	} else {
		length += pt;
	}
	int significant = std::min(length, 17);
	double adjust = pow(10.0, -significant) * 5;

	char *ptr = (char *)alloca(length + 4 + (pt < 0 ? -pt : 0)) + 3;
	char *end = ptr;
	char *dot = nullptr;

	if (pt < 0) {
		int n = -pt;
		if (n > precision) {
			n = precision;
		}
		if (n > 0) {
			*end++ = '.';
			for (int i = 0; i < n; i++) {
				*end++ = '0';
			}
			if (length > n) {
				length -= n;
			}
		}
	}

	for (int i = 0; i < length; i++) {
		if (i == pt) {
			dot = end;
			*end++ = '.';
		}
		if (i < significant) {
			val *= 10;
			double v = floor(val);
			val -= v;
			val += adjust;
			adjust = 0;
			*end++ = (int)v + '0';
		} else {
			*end++ = '0';
		}
	}

	if (ptr == end) {
		*end++ = '0';
	} else {
		if (*ptr == '.') {
			*--ptr = '0';
		}
	}

	if (sign) {
		*--ptr = '-';
	} else if (force_sign) {
		*--ptr = '+';
	}

	if (trim_unnecessary_zeros && dot) {
		while (dot < end) {
			char c = end[-1];
			if (c == '.') {
				end--;
				break;
			}
			if (c != '0') {
				break;
			}
			end--;
		}
	}

	return alloc_part(ptr, end);
}

Part *format_int32(int32_t val, bool force_sign)
{
	int n = 30;
	char *end = (char *)alloca(n) + n - 1;
	char *ptr = end;
	*end = 0;

	if (val == 0) {
		*--ptr = '0';
	} else {
		if (val == (int32_t)1 << 31) {
			*--ptr = '8';
			val /= 10;
		}
		bool sign = (val < 0);
		if (sign) val = -val;

		while (val != 0) {
			int c = val % 10 + '0';
			val /= 10;
			*--ptr = c;
		}
		if (sign) {
			*--ptr = '-';
		} else if (force_sign) {
			*--ptr = '+';
		}
	}

	return alloc_part(ptr, end);
}

Part *format_uint32(uint32_t val)
{
	int n = 30;
	char *end = (char *)alloca(n) + n - 1;
	char *ptr = end;
	*end = 0;

	if (val == 0) {
		*--ptr = '0';
	} else {
		while (val != 0) {
			int c = val % 10 + '0';
			val /= 10;
			*--ptr = c;
		}
	}

	return alloc_part(ptr, end);
}

Part *format_int64(int64_t val, bool force_sign)
{
	int n = 30;
	char *end = (char *)alloca(n) + n - 1;
	char *ptr = end;
	*end = 0;

	if (val == 0) {
		*--ptr = '0';
	} else {
		if (val == (int64_t)1 << 63) {
			*--ptr = '8';
			val /= 10;
		}
		bool sign = (val < 0);
		if (sign) val = -val;

		while (val != 0) {
			int c = val % 10 + '0';
			val /= 10;
			*--ptr = c;
		}
		if (sign) {
			*--ptr = '-';
		} else if (force_sign) {
			*--ptr = '+';
		}
	}

	return alloc_part(ptr, end);
}

Part *format_uint64(uint64_t val)
{
	int n = 30;
	char *end = (char *)alloca(n) + n - 1;
	char *ptr = end;
	*end = 0;

	if (val == 0) {
		*--ptr = '0';
	} else {
		while (val != 0) {
			int c = val % 10 + '0';
			val /= 10;
			*--ptr = c;
		}
	}

	return alloc_part(ptr, end);
}

Part *format_oct32(uint32_t val, bool upper)
{
	int n = 30;
	char *end = (char *)alloca(n) + n - 1;
	char *ptr = end;
	*end = 0;

	char const *digits = upper ? digits_upper : digits_lower;

	if (val == 0) {
		*--ptr = '0';
	} else {
		while (val != 0) {
			char c = digits[val & 7];
			val >>= 3;
			*--ptr = c;
		}
	}

	return alloc_part(ptr, end);
}

Part *format_oct64(uint64_t val, bool upper)
{
	int n = 30;
	char *end = (char *)alloca(n) + n - 1;
	char *ptr = end;
	*end = 0;

	char const *digits = upper ? digits_upper : digits_lower;

	if (val == 0) {
		*--ptr = '0';
	} else {
		while (val != 0) {
			char c = digits[val & 7];
			val >>= 3;
			*--ptr = c;
		}
	}

	return alloc_part(ptr, end);
}

Part *format_hex32(uint32_t val, bool upper)
{
	int n = 30;
	char *end = (char *)alloca(n) + n - 1;
	char *ptr = end;
	*end = 0;

	char const *digits = upper ? digits_upper : digits_lower;

	if (val == 0) {
		*--ptr = '0';
	} else {
		while (val != 0) {
			char c = digits[val & 15];
			val >>= 4;
			*--ptr = c;
		}
	}

	return alloc_part(ptr, end);
}

Part *format_hex64(uint64_t val, bool upper)
{
	int n = 30;
	char *end = (char *)alloca(n) + n - 1;
	char *ptr = end;
	*end = 0;

	char const *digits = upper ? digits_upper : digits_lower;

	if (val == 0) {
		*--ptr = '0';
	} else {
		while (val != 0) {
			char c = digits[val & 15];
			val >>= 4;
			*--ptr = c;
		}
	}

	return alloc_part(ptr, end);
}

Part *format_pointer(void *val)
{
	int n = sizeof(uintptr_t) * 2 + 1;
	char *end = (char *)alloca(n) + n - 1;
	char *ptr = end;
	*end = 0;

	uintptr_t v = (uintptr_t)val;
	for (int i = 0; i < (int)sizeof(uintptr_t) * 2; i++) {
		char c = digits_upper[v & 15];
		v >>= 4;
		*--ptr = c;
	}

	return alloc_part(ptr, end);
}

struct NumberTraits {
	char const *p;
	bool sign = false;
	int radix = 10;
	NumberTraits(char const *ptr)
		: p(ptr)
	{
		while (isspace((unsigned char)*p)) {
			p++;
		}
		if (*p == '+') {
			p++;
		} else if (*p == '-') {
			sign = true;
			p++;
		}
		if (p[0] == '0') {
			if (p[1] == 'x') {
				p += 2;
				radix = 16;
			} else {
				int i = 1;
				while (1) {
					int c = (unsigned char)p[i];
					if (c == '.') {
						break;
					}
					if (!isdigit(c)) {
						radix = 8;
					}
					i++;
				}
			}
		}
	}
};

template <typename T> T parse_number(char const *ptr, std::function<T(char const *p, int radix)> conv)
{
	NumberTraits t(ptr);
	T v = conv(t.p, t.radix);
	if (t.sign) v = -v;
	return v;
}

template <typename T> T num(char const *value);
template <> char num<char>(char const *value)
{
	return parse_number<char>(value, [](char const *p, int radix){
		return (char)strtol(p, nullptr, radix);
	});
}
template <> int32_t num<int32_t>(char const *value)
{
	return parse_number<int32_t>(value, [](char const *p, int radix){
		return strtol(p, nullptr, radix);
	});
}
template <> uint32_t num<uint32_t>(char const *value)
{
	return parse_number<uint32_t>(value, [](char const *p, int radix){
		return strtoul(p, nullptr, radix);
	});
}
template <> int64_t num<int64_t>(char const *value)
{
	return parse_number<int64_t>(value, [](char const *p, int radix){
		return strtoll(p, nullptr, radix);
	});
}
template <> uint64_t num<uint64_t>(char const *value)
{
	return parse_number<uint64_t>(value, [](char const *p, int radix){
		return strtoull(p, nullptr, radix);
	});
}
template <> double num<double>(char const *value)
{
	return parse_number<double>(value, [](char const *p, int radix){
		if (radix == 10) {
			return strtod(p, nullptr);
		} else {
			return (double)strtoll(p, nullptr, radix);
		}
	});
}
template <typename T> T num(std::string const &value)
{
	return num<T>(value.c_str());
}

} // namespace

// strformat class

strformat::strformat(const std::string &text)
	: text_(text)
{
	reset();
}

strformat::~strformat()
{
	clear();
}

inline void strformat::clear()
{
	free_list(&list_);
}

bool strformat::advance()
{
	bool r = false;
	auto Flush = [&](){
		if (head_ < next_) {
			Part *p = alloc_part(head_, next_);
			add_part(&list_, p);
			head_ = next_;
		}
	};
	while (*next_) {
		if (*next_ == '%') {
			if (next_[1] == '%') {
				next_++;
				Flush();
				next_++;
				head_ = next_;
			} else {
				r = true;
				break;
			}
		} else {
			next_++;
		}
	}
	Flush();
	return r;
}

inline Part *strformat::format_f(double value, bool trim_unnecessary_zeros)
{
	int pr = precision_ < 0 ? 6 : precision_;
	return format_double(value, pr, trim_unnecessary_zeros, force_sign_);
}

inline Part *strformat::format_c(char c)
{
	return alloc_part(&c, &c + 1);
}

Part *strformat::format_o32(int32_t value, int hint)
{
	if (hint) {
		switch (hint) {
		case 'c': return format_c((char)value);
		case 'd': return format((int32_t)value, 0);
		case 'u': return format((uint32_t)value, 0);
		case 'x': return format_x32((uint32_t)value, 0);
		case 'f': return format((double)value, 0);
		}
	}
	return format_oct32(value, upper_);
}

Part *strformat::format_o64(int64_t value, int hint)
{
	if (hint) {
		switch (hint) {
		case 'c': return format_c((char)value);
		case 'd': return format((int64_t)value, 0);
		case 'u': return format((uint64_t)value, 0);
		case 'x': return format_x64((uint64_t)value, 0);
		case 'f': return format((double)value, 0);
		}
	}
	return format_oct64(value, upper_);
}

Part *strformat::format_x32(int32_t value, int hint)
{
	if (hint) {
		switch (hint) {
		case 'c': return format_c((char)value);
		case 'd': return format((int32_t)value, 0);
		case 'u': return format((uint32_t)value, 0);
		case 'o': return format_o32((uint32_t)value, 0);
		case 'f': return format((double)value, 0);
		}
	}
	return format_hex32(value, upper_);
}

Part *strformat::format_x64(int64_t value, int hint)
{
	if (hint) {
		switch (hint) {
		case 'c': return format_c((char)value);
		case 'd': return format((int64_t)value, 0);
		case 'u': return format((uint64_t)value, 0);
		case 'o': return format_o64((uint64_t)value, 0);
		case 'f': return format((double)value, 0);
		}
	}
	return format_hex64(value, upper_);
}

Part *strformat::format(char c, int hint)
{
	return format((int32_t)c, hint);
}

Part *strformat::format(double value, int hint)
{
	if (hint) {
		switch (hint) {
		case 'c': return format_c((char)value);
		case 'd': return format((int64_t)value, 0);
		case 'u': return format((uint64_t)value, 0);
		case 'o': return format_o64((uint64_t)value, 0);
		case 'x': return format_x64((uint64_t)value, 0);
		case 's': return format_f(value, true);
		}
	}
	return format_f(value, false);
}

Part *strformat::format(int32_t value, int hint)
{
	if (hint) {
		switch (hint) {
		case 'c': return format_c((char)value);
		case 'u': return format((uint32_t)value, 0);
		case 'o': return format_o32((uint32_t)value, 0);
		case 'x': return format_x32((uint32_t)value, 0);
		case 'f': return format((double)value, 0);
		}
	}
	return format_int32(value, force_sign_);
}

Part *strformat::format(uint32_t value, int hint)
{
	if (hint) {
		switch (hint) {
		case 'c': return format_c((char)value);
		case 'd': return format((int32_t)value, 0);
		case 'o': return format_o32((uint32_t)value, 0);
		case 'x': return format_x32((uint32_t)value, 0);
		case 'f': return format((double)value, 0);
		}
	}
	return format_uint32(value);
}

Part *strformat::format(int64_t value, int hint)
{
	if (hint) {
		switch (hint) {
		case 'c': return format_c((char)value);
		case 'u': return format((uint64_t)value, 0);
		case 'o': return format_o64((uint64_t)value, 0);
		case 'x': return format_x64((uint64_t)value, 0);
		case 'f': return format((double)value, 0);
		}
	}
	return format_int64(value, force_sign_);
}

Part *strformat::format(uint64_t value, int hint)
{
	if (hint) {
		switch (hint) {
		case 'c': return format_c((char)value);
		case 'd': return format((int64_t)value, 0);
		case 'o': return format_oct64(value, false);
		case 'x': return format_hex64(value, false);
		case 'f': return format((double)value, 0);
		}
	}
	return format_uint64(value);
}

Part *strformat::format(const char *value, int hint)
{
	if (!value) {
		return alloc_part("(null)");
	}
	if (hint) {
		switch (hint) {
		case 'c':
			return format(num<char>(value), hint);
		case 'd':
			if (lflag_ == 0) {
				return format(num<int32_t>(value), 0);
			} else {
				return format(num<int64_t>(value), 0);
			}
		case 'u': case 'o': case 'x':
			if (lflag_ == 0) {
				return format(num<uint32_t>(value), hint);
			} else {
				return format(num<uint64_t>(value), hint);
			}
		case 'f':
			return format(num<double>(value), hint);
		}
	}
	return alloc_part(value, value + strlen(value));
}

Part *strformat::format(const std::string &value, int hint)
{
	if (hint == 's') {
		return alloc_part(value);
	}
	return format(value.c_str(), hint);
}

Part *strformat::format_p(void *val)
{
	return format_pointer(val);
}

void strformat::format(std::function<Part *(int)> callback, int width, int precision)
{
	if (advance()) {
		if (*next_ == '%') {
			next_++;
		}

		upper_ = false;
		zero_padding_ = false;
		align_left_ = false;
		force_sign_ = false;
		width_ = -1;
		precision_ = -1;
		lflag_ = 0;

		while (1) {
			int c = (unsigned char)*next_;
			if (c == '0') {
				zero_padding_ = true;
			} else if (c == '+') {
				force_sign_ = true;
			} else if (c == '-') {
				align_left_ = true;
			} else {
				break;
			}
			next_++;
		}

		auto GetNumber = [&](int alternate_value){
			int value = -1;
			if (*next_ == '*') {
				next_++;
			} else {
				while (1) {
					int c = (unsigned char)*next_;
					if (!isdigit(c)) break;
					if (value < 0) {
						value = 0;
					} else {
						value *= 10;
					}
					value += c - '0';
					next_++;
				}
			}
			if (value < 0) {
				value = alternate_value;
			}
			return value;
		};

		width_ = GetNumber(width);

		if (*next_ == '.') {
			next_++;
		}

		precision_ = GetNumber(precision);

		while (*next_ == 'l') {
			lflag_++;
			next_++;
		}

		Part *p = nullptr;

		int c = (unsigned char)*next_;
		if (isupper(c)) {
			upper_ = true;
			c = tolower(c);
		}
		if (isalpha(c)) {
			p = callback(c);
			next_++;
		}
		if (p) {
			int padlen = width_ - p->size;
			if (padlen > 0 && !align_left_) {
				if (zero_padding_) {
					char c = p->data[0];
					add_chars(&list_, '0', padlen);
					if (c == '+' || c == '-') {
						list_.last->data[0] = c;
						p->data[0] = '0';
					}
				} else {
					add_chars(&list_, ' ', padlen);
				}
			}

			add_part(&list_, p);

			if (padlen > 0 && align_left_) {
				add_chars(&list_, ' ', padlen);
			}
		}

		head_ = next_;
	}
}

strformat &strformat::reset()
{
	clear();
	head_ = text_.c_str();
	next_ = head_;
	return *this;
}

void strformat::destroy()
{
	text_.clear();
	reset();
}

strformat &strformat::append(const std::string &s)
{
	text_ += s;
	return *this;
}

strformat &strformat::append(const char *s)
{
	text_ += s;
	return *this;
}



void strformat::vec(std::vector<char> *vec)
{
	advance();
	int len = 0;
	for (Part *p = list_.head; p; p = p->next) {
		len += p->size;
	}
	vec->reserve(vec->size() + len);
	for (Part *p = list_.head; p; p = p->next) {
		vec->insert(vec->end(), p->data, p->data + p->size);
	}
}

void strformat::render(std::function<void (char const *, int)> dst)
{
	std::vector<char> v;
	vec(&v);
	if (!v.empty()) {
		dst(&v[0], (int)v.size());
	}
}

void strformat::write_to(FILE *fp)
{
	render([&](char const *ptr, int len){
		fwrite(ptr, 1, len, fp);
	});
}

void strformat::write_to(int fd)
{
	render([&](char const *ptr, int len){
		::write(fd, ptr, len);
	});
}

void strformat::out()
{
	write_to(stdout);
}

void strformat::err()
{
	write_to(stderr);
}

std::string strformat::str()
{
	std::string r;
	render([&](char const *ptr, int len){
		r.assign(ptr, len);
	});
	return r;
}

