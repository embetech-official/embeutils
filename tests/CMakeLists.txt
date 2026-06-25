add_executable(embeutils_ut)
target_compile_features(embeutils_ut PRIVATE cxx_std_20)

target_sources(
  embeutils_ut
  PRIVATE ut_compiler_support.cpp
          ut_endianness.cpp
          ut_expect.cpp
          ut_expect_extra_off.cpp
          ut_expect_extra_on.cpp
          ut_expect_verbosity.cpp
          ut_semver.cpp
  PRIVATE FILE_SET HEADERS BASE_DIRS include
)

target_link_libraries(embeutils_ut PRIVATE embetech::utils gtest_main)

include(GoogleTest)
gtest_discover_tests(embeutils_ut)
