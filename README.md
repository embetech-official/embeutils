# Embeutils - utilities for embedded firmware projects

This is a small header-only library with some tools that are usefull for embedded firmware projects.\
The tools include:
- compiler_support.h which provides a set of macros controlling compiler-specific attributes
- endianess.h which provides tools for manipulating the endianess
- expect.h which provides a set of tools to organize error handling and make it more explicit

## Installation

While there are many methods, the intended way of working with this component is to include the library as a CMake dependency in your project using the [**FetchContent**](https://cmake.org/cmake/help/latest/module/FetchContent.html) CMake module.

## Usage

Just include the header file and use its contents.
