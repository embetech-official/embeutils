cmake_minimum_required(VERSION 3.25)

file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION.txt" PROJECT_VERSION)
project(embeutils VERSION ${PROJECT_VERSION})

# The verbose messages are enabled by default in Debug builds. If you want to force DISABLE them,
# you need to unset the cache variable and set non-cache variable to OFF
option(EMBEUTILS_EXPECT_VERBOSE "Forces verbose messages in abort handler" OFF)
option(EMBEUTILS_EXTRA_CHECKS "Enables additional checks at runtime" OFF)

option(EMBEUTILS_TESTS "Build test cases" ${PROJECT_IS_TOP_LEVEL})
option(EMBEUTILS_EXAMPLES "Build examples" ${PROJECT_IS_TOP_LEVEL})
option(EMBEUTILS_DOC "Build documentation" ${PROJECT_IS_TOP_LEVEL})
option(EMBEUTILS_INSTALL "Configure install target" ON)

add_subdirectory(src)

include(cmake/requirements.cmake)

if (EMBEUTILS_DOC)
  add_subdirectory(doc)
endif ()

if (EMBEUTILS_TESTS)
  include(CTest)
  add_subdirectory(tests)
endif ()

if (EMBEUTILS_TESTS)
  add_subdirectory(examples)
endif ()

if (EMBEUTILS_INSTALL)
  include(cmake/install.cmake)
endif ()
