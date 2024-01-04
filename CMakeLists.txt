cmake_minimum_required(VERSION 3.20)

project(embeutils VERSION 1.0.0 LANGUAGES C)

option(CONFIG_EMBEUTILS_EXPECT_VERBOSE "Enables verbose messages in abort handler" OFF)

option(CONFIG_EMBEUTILS_EXTRA_CHECKS "Enables additional checks at runtime" OFF)

option(CONFIG_EMBEUTILS_TESTS "Configures test cases" ${PROJECT_IS_TOP_LEVEL})

option(CONFIG_EMBEUTILS_INSTALL "Configures install target" ${PROJECT_IS_TOP_LEVEL})

add_subdirectory(src)

if (CONFIG_EMBEUTILS_TESTS)
  enable_testing()
  add_subdirectory(tests EXCLUDE_FROM_ALL)
endif ()
