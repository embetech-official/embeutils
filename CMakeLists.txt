cmake_minimum_required(VERSION 3.25)

file(READ "${CMAKE_CURRENT_LIST_DIR}/../VERSION" PROJECT_VERSION)
project(embeutils VERSION ${PROJECT_VERSION} LANGUAGES CXX C)

# The verbose messages are enabled by default in Debug builds. If you want to force DISABLE them,
# you need to unset the cache variable and set non-cache variable to OFF
option(EMBEUTILS_EXPECT_VERBOSE "Forces verbose messages in abort handler" OFF)
option(EMBEUTILS_EXTRA_CHECKS "Enables additional checks at runtime" OFF)

option(EMBEUTILS_TESTS "Build test cases" ${PROJECT_IS_TOP_LEVEL})
option(EMBEUTILS_EXAMPLES "Build examples" ${PROJECT_IS_TOP_LEVEL})
option(EMBEUTILS_DOC "Build documentation" ${PROJECT_IS_TOP_LEVEL})
option(EMBEUTILS_INSTALL "Configure install target" ON)

add_subdirectory(src)

if (EMBEUTILS_DOC)
  add_subdirectory(doc EXCLUDE_FROM_ALL)
endif ()

if (EMBEUTILS_TESTS)
  include(CTest)
  add_subdirectory(tests EXCLUDE_FROM_ALL)
endif ()

if (EMBEUTILS_TESTS)
  add_subdirectory(examples EXCLUDE_FROM_ALL)
endif ()

if (EMBEUTILS_INSTALL)
  include(cmake/install.cmake)
endif ()
