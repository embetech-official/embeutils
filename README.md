# Embeutils - utilities for embedded firmware projects

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/b845bae66613482a8847ed05b6269ed5)](https://app.codacy.com/gh/embetech-official/embeutils?utm_source=github.com&utm_medium=referral&utm_content=embetech-official/embeutils&utm_campaign=Badge_Grade)

This is a small header-only library with some tools that are usefull for embedded firmware projects.\
The tools include:
- compiler_support.h which provides a set of macros controlling compiler-specific attributes
- endianess.h which provides tools for manipulating the endianess
- expect.h which provides a set of tools to organize error handling and make it more explicit

## Installation

While there are many methods, the intended way of working with this component is to include the library as a CMake dependency in your project using the [**FetchContent**](https://cmake.org/cmake/help/latest/module/FetchContent.html) CMake module.

## Usage

Just include the header file and use its contents.
