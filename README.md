# Embeutils - utilities for embedded firmware projects

[![Unit Tests](https://github.com/embetech-official/embeutils/actions/workflows/unit_tests.yml/badge.svg)](https://github.com/embetech-official/embeutils/actions/workflows/unit_tests.yml)
![GitHub Release](https://img.shields.io/github/v/release/embetech-official/embeutils)
![GitHub License](https://img.shields.io/github/license/embetech-official/embeutils)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/dfab6840a2af4fb890993c76798a587e)](https://app.codacy.com/gh/embetech-official/embeutils/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=embetech-official_logger&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=embetech-official_logger)

This is a small header-only library with some tools that are usefull for embedded firmware projects.\
The tools include:
- compiler_support.h which provides a set of macros controlling compiler-specific attributes
- endianess.h which provides tools for manipulating the endianess
- expect.h which provides a set of tools to organize error handling and make it more explicit

## Installation

While there are many methods, the intended way of working with this component is to include the library as a CMake dependency in your project using the [**FetchContent**](https://cmake.org/cmake/help/latest/module/FetchContent.html) CMake module.

## Usage

Just include the header file and use its contents.
