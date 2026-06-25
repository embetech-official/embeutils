# Embeutils - utilities for embedded firmware projects

[![CI](https://github.com/embetech-official/embeutils/actions/workflows/on_push.yml/badge.svg)](https://github.com/embetech-official/embeutils/actions/workflows/on_push.yml)
![GitHub Release](https://img.shields.io/github/v/release/embetech-official/embeutils)
![GitHub License](https://img.shields.io/github/license/embetech-official/embeutils)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/dfab6840a2af4fb890993c76798a587e)](https://app.codacy.com/gh/embetech-official/embeutils/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)

A small header-only C library with utilities for embedded firmware projects. Requires C11 or C++20.

The library includes:

- `compiler_support.h` — portable macros for compiler-specific attributes
- `endianness.h` — byte-order conversion utilities
- `expect.h` — explicit error handling macros
- `semantic_version.h` — semantic version representation, comparison, and parsing

## Quick start

### 1. Get the library

```cmake
include(FetchContent)

FetchContent_Declare(
  embeutils
  URL https://github.com/embetech-official/embeutils/archive/refs/tags/v1.3.0.zip
)

FetchContent_MakeAvailable(embeutils)
```

### 2. Link with your target

```cmake
target_link_libraries(my_target PRIVATE embetech::utils)
```

### 3. Use it

```c
#include <embetech/expect.h>

bool parse_packet(uint8_t const *buf, size_t len) {
    EXPECT(buf != NULL) OR_RETURN(false);
    EXPECT(len >= HEADER_SIZE) OR_ABORT("packet too short");
    // ...
    return true;
}
```

## Components

### `compiler_support.h` — Compiler attribute macros

Portable wrappers for compiler-specific attributes, so you can write clean, warning-free code across GCC, Clang, and MSVC.

| Macro | Purpose |
| --- | --- |
| `EMBEUTILS_STATIC_ASSERT(cond, msg)` | Compile-time assertion |
| `EMBEUTILS_PACK_BEGIN` / `EMBEUTILS_PACK_END` | Packed struct delimiters |
| `EMBEUTILS_ALIGNAS(n)` / `EMBEUTILS_ALIGNOF(t)` | Alignment specifier / query |
| `EMBEUTILS_NORETURN` | Function never returns |
| `EMBEUTILS_NODISCARD` | Warn if return value is discarded |
| `EMBEUTILS_INLINE` | Force-inline hint |
| `EMBEUTILS_NONNULL(...)` | Mark pointer parameters as non-null |
| `EMBEUTILS_UNUSED` | Suppress unused-variable warnings |
| `EMBEUTILS_RESTRICT` | Portable `restrict` qualifier |
| `EMBEUTILS_FALLTHROUGH` | Intentional switch fallthrough |
| `EMBEUTILS_WEAK` | Weak symbol (overridable by linker) |

### `endianness.h` — Byte-order conversion

Functions to convert between little-endian, big-endian, and host byte order. Includes generic-selection macros under C11.

```c
#include <embetech/endianness.h>

uint32_t net  = ENDIANNESS_hton32(0x12345678); // host → network (big-endian)
uint32_t host = ENDIANNESS_ntoh32(net);         // network → host

uint32_t le = ENDIANNESS_NativeToLittle32(value);
uint32_t be = ENDIANNESS_NativeToBig32(value);
```

### `expect.h` — Explicit error handling

Macros that make precondition checking and error propagation explicit and readable.

```c
#include <embetech/expect.h>

bool my_function(void *data, size_t size) {
    EXPECT(data != NULL) OR_RETURN(false);   // returns false on failure
    EXPECT(size > 0)     OR_ABORT("size must be positive"); // aborts on failure
    EXPECT_EXTRA(size < MAX_SIZE) OR_RETURN(false); // only active when EMBEUTILS_EXTRA_CHECKS is set
    return true;
}
```

`EXPECT_EXTRA` is intended for checks that are too expensive for production builds and is compiled out unless `EMBEUTILS_EXTRA_CHECKS` is defined.

### `semantic_version.h` — Semantic versioning

Binary representation of a semantic version (`major.minor.patch+id`) with parsing and comparison utilities.

```c
#include <embetech/semantic_version.h>

SemanticVersion v = SEMVER_Parse("1.3.0+deadbeef");
if (SEMVER_IsValid(v)) {
    // v.major == 1, v.minor == 3, v.patch == 0, v.id == 0xDEADBEEF
}

SemanticVersion current = {1, 2, 0, 0};
SemanticVersion latest  = {1, 3, 0, 0};
if (SEMVER_IsNewer(latest, current)) {
    // firmware update available
}
```

The `id` field (e.g. a git commit hash) is not used in ordering comparisons.

## Configuration

Both options are **enabled by default in Debug builds** and **disabled in Release builds**.

| CMake variable | Default | Effect |
| --- | --- | --- |
| `EMBEUTILS_EXPECT_VERBOSE` | ON in Debug | Includes reason strings in the abort handler output |
| `EMBEUTILS_EXTRA_CHECKS` | ON in Debug | Enables `EXPECT_EXTRA` runtime checks |

> [!IMPORTANT]
> To force-disable an option in a Debug build, unset the corresponding CMake cache variable and set it as a non-cache variable to `OFF`.

## Building and testing

The library is header-only — no compilation is needed for use. Tests require CMake 3.25+, Ninja, and a C++20-capable GCC.

```sh
cmake --workflow --preset native-gcc
```

This configures, builds (Debug + Release), runs all 57 unit tests, and installs headers.
