cmake_minimum_required(VERSION 3.20)

project(embeutils VERSION 1.0.0 LANGUAGES C)

option(CONFIG_EMBEUTILS_EXPECT_VERBOSE "Enables verbose messages in abort handler" OFF)

option(CONFIG_EMBEUTILS_EXTRA_CHECKS "Enables additional checks at runtime" OFF)

option(CONFIG_EMBEUTILS_BUILD_TESTS "Forces building test cases" PROJECT_IS_TOP_LEVEL)

include(requirements.cmake)

if (CONFIG_EMBEUTILS_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif ()
