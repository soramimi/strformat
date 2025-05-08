[![Ask DeepWiki](https://deepwiki.com/badge.svg)](https://deepwiki.com/soramimi/strformat)

# strformat

A lightweight, header-only string formatting library for C++ that provides printf-style formatting with a fluent, chainable API.

## Overview

strformat is a modern C++ string formatting library that:

- Is header-only for simple integration
- Provides printf-style format specifiers
- Uses method chaining for a clean API
- Supports cross-platform development (Windows, Linux)
- Offers locale-independent formatting
- Supports formatting of integers, floating-point numbers, characters, strings, and pointers
- Handles width, precision, alignment, and padding options

## Requirements

- C++17 compatible compiler
- No external dependencies

## Getting Started

Simply include the `strformat.h` header file in your project:

```cpp
#include "strformat.h"
```

## Basic Usage

```cpp
#include "strformat.h"
#include <iostream>

int main() {
    // Format to string
    std::string result = strformat("Hello, %s! The answer is %d.")
                        .s("world")
                        .d(42)
                        .str();
    std::cout << result << std::endl;
    
    // Direct output to stdout
    strformat("Hello, %s! The answer is %d.")
        .s("world")
        .d(42)
        .put();
        
    // Direct output to stderr
    strformat("Error code: %d").d(-1).err();
    
    return 0;
}
```

## Format Specifiers

strformat supports the following format specifiers:

- `%d` - 32-bit signed integer
- `%ld` - 64-bit signed integer
- `%u` - 32-bit unsigned integer
- `%lu` - 64-bit unsigned integer
- `%f` - Floating-point number
- `%s` - String
- `%c` - Character
- `%x` - Hexadecimal (lowercase)
- `%X` - Hexadecimal (uppercase)
- `%o` - Octal
- `%p` - Pointer

## Formatting Options

Various formatting options are available:

```cpp
// Width and padding
strformat("%10d").d(123);       // "       123"
strformat("%010d").d(123);      // "0000000123"
strformat("%-10d").d(123);      // "123       "

// Sign control
strformat("%+d").d(123);        // "+123"

// Precision for floating-point numbers
strformat("%.2f").f(123.456);   // "123.46"

// Combined options
strformat("%+10.2f").f(123.456); // "    +123.46"
```

## Method Chaining

You can chain multiple formatting operations:

```cpp
std::string result = strformat("Name: %s, Age: %d, Balance: $%.2f")
                    .s("John Doe")
                    .d(35)
                    .f(1234.567)
                    .str();
```

## Output Options

strformat provides several output options:

```cpp
// Get as string
std::string result = strformat("Value: %d").d(123).str();

// Write to stdout
strformat("Value: %d").d(123).put();

// Write to stderr
strformat("Error: %d").d(123).err();

// Write to a FILE pointer
FILE* fp = fopen("output.txt", "w");
strformat("Value: %d").d(123).write_to(fp);
fclose(fp);

// Write to a file descriptor
strformat("Value: %d").d(123).write_to(fd);

// Append to a vector
std::vector<char> buffer;
strformat("Value: %d").d(123).vec(&buffer);
```

## Build Options

To disable floating-point support (for smaller footprint):

```cpp
#define STRFORMAT_NO_FP
#include "strformat.h"
```

## Building the Project

### Linux

```bash
# Using make
make

# Using qmake
./mk.sh
cd _build
make
```

### Windows

Open the Visual Studio solution file `strformat.sln` and build the project.

## License

This software is distributed under the MIT license.

Copyright (C) 2024 S.Fuchita (soramimi_jp)