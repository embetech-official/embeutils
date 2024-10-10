cmake_minimum_required(VERSION 3.25)

project(embeutils VERSION 1.0.1)

option(EMBEUTILS_EXPECT_VERBOSE "Enables verbose messages in abort handler" OFF)

option(EMBEUTILS_EXTRA_CHECKS "Enables additional checks at runtime" OFF)

option(EMBEUTILS_TESTS "Build test cases" ${PROJECT_IS_TOP_LEVEL})

option(EMBEUTILS_INSTALL "Configure install target" ON)

add_subdirectory(src)

if (EMBEUTILS_TESTS)
  include(CTest)
  enable_testing()
  add_subdirectory(tests EXCLUDE_FROM_ALL)
endif ()

if (EMBEUTILS_INSTALL)
  include(cmake/install.cmake)
endif ()
