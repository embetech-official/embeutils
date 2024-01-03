project(embeutils_ut LANGUAGES CXX C)

FetchContent_MakeAvailable(googletest)

add_executable(embeutils_ut embeutils_ut.cpp)
target_link_libraries(embeutils_ut PRIVATE embetech::utils gtest_main)
include(GoogleTest)
gtest_discover_tests(embeutils_ut)
