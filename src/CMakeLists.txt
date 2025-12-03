add_library(embeutils INTERFACE)
add_library(embetech::utils ALIAS embeutils)
set_target_properties(embeutils PROPERTIES EXPORT_NAME utils)

target_sources(
  embeutils
  INTERFACE FILE_SET
            HEADERS
            BASE_DIRS
            include
            FILES
            include/embetech/compiler_support.h
            include/embetech/endianness.h
            include/embetech/expect.h
            include/embetech/semantic_version.h
)

if (EMBEUTILS_EXPECT_VERBOSE)
  # Force enabled verbose
  target_compile_definitions(embeutils INTERFACE EMBEUTILS_EXPECT_VERBOSE=1)
elseif (NOT DEFINED CACHE{EMBEUTILS_EXPECT_VERBOSE})
  # Force disable (cache unset, and non-cache set to OFF)
  target_compile_definitions(embeutils INTERFACE EMBEUTILS_EXPECT_VERBOSE=0)
else ()
  target_compile_definitions(embeutils INTERFACE $<$<CONFIG:Debug>:EMBEUTILS_EXPECT_VERBOSE=1>)
endif ()

if (EMBEUTILS_EXTRA_CHECKS)
  target_compile_definitions(embeutils INTERFACE EMBEUTILS_EXTRA_CHECKS=1)

elseif (NOT DEFINED CACHE{EMBEUTILS_EXTRA_CHECKS})
  # Force disable (cache unset, and non-cache set to OFF)
  target_compile_definitions(embeutils INTERFACE EMBEUTILS_EXTRA_CHECKS=0)
else ()
  target_compile_definitions(embeutils INTERFACE $<$<CONFIG:Debug>:EMBEUTILS_EXTRA_CHECKS=1>)
endif ()
