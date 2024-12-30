project(embeutils_ut)

include(FetchContent)

cmake_policy(SET CMP0135 NEW)
FetchContent_Declare(
  googletest URL https://github.com/google/googletest/archive/main.zip FIND_PACKAGE_ARGS NAMES
                 GTest
)
FetchContent_MakeAvailable(googletest)

# Workaround for https://github.com/google/googletest/issues/4671
target_compile_options(gtest PRIVATE -Wno-null-dereference)

add_executable(
  embeutils_ut ut_expect.cpp ut_expect_extra_off.cpp ut_expect_extra_on.cpp ut_expect_verbosity.cpp
)
target_link_libraries(embeutils_ut PRIVATE embetech::utils gtest_main)
include(GoogleTest)
gtest_discover_tests(embeutils_ut)
