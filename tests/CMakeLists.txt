project(embeutils_ut LANGUAGES CXX C)

include(FetchContent)

cmake_policy(SET CMP0135 NEW)
FetchContent_Declare(
  googletest URL https://github.com/google/googletest/archive/main.zip FIND_PACKAGE_ARGS NAMES
                 GTest
)
FetchContent_MakeAvailable(googletest)

target_compile_options(
  embeutils
  INTERFACE -Werror
            -Wall
            -Wextra
            -Wpedantic
            -Wformat=2
            -Wformat-overflow=2
            -Wformat-security
            -Wformat-signedness
            -Wunused-parameter
            -Winit-self
            -Wcast-align
            -Wconversion
            -Wpedantic
            -Wnull-dereference
            -Wduplicated-cond
            -Wnull-dereference
            -Wsign-conversion
            -Wlogical-op
)

add_executable(embeutils_ut embeutils_ut.cpp)
target_link_libraries(embeutils_ut PRIVATE embetech::utils gtest_main)
include(GoogleTest)
gtest_discover_tests(embeutils_ut)
