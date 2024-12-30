# Embeutils - utilities for embedded firmware projects

[![Unit Tests](https://github.com/embetech-official/embeutils/actions/workflows/unit_tests.yml/badge.svg)](https://github.com/embetech-official/embeutils/actions/workflows/unit_tests.yml)
![GitHub Release](https://img.shields.io/github/v/release/embetech-official/embeutils)
![GitHub License](https://img.shields.io/github/license/embetech-official/embeutils)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/dfab6840a2af4fb890993c76798a587e)](https://app.codacy.com/gh/embetech-official/embeutils/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=embetech-official_embeutils&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=embetech-official_embeutils)

This is a small header-only library with some tools that are usefull for embedded firmware projects.\
The tools include:
- compiler_support.h which provides a set of macros controlling compiler-specific attributes
- endianess.h which provides tools for manipulating the endianess
- expect.h which provides a set of tools to organize error handling and make it more explicit

## Quick start
### 1. Get the library
```cmake
include(FetchContent)

# Remove FIND_PACKAGE_ARGS when using CMake < 3.24
FetchContent_Declare(embeutils https://github.com/embetech-official/embeutils/archive/refs/tags/v1.zip FIND_PACKAGE_ARGS)


# If you need to set configuration options, this is the last spot to do so

FetchContent_MakeAvailable(embeutils)
```


### 2. Link with your target
```cmake
target_link_libraries(my_target PRIVATE embetech::utils)
```

### 3. All set to go
```c
#include <embetech/expect.h>

void do_work(void* data) {
    EXPECT(data != NULL) OR_ABORT("data must be non-null");
}
```

## Components

### Endianness support
The component provides functions to convert data representation between little- and big-endian.
When using C11 compliant compiler, there are Generic selection conversion macros.

### Compiler support

### Contracts


## Configuration
- **EMBEUTILS_EXPECT_VERBOSE**: Force enables verbose messages in EXPECT macros.

- **EMBEUTILS_EXTRA_CHECKS** : Force enables additional runtime checks (executed via **EXPECT_EXTRA** macro)

> [!IMPORTANT]
> The default behaviour is to enable both EXPECT_EXTRA and verbose messages in DEBUG build configuration. If you wish to force **disable** the options, unset appropriate cache variables and set non-cache variables to OFF
