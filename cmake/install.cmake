include(CMakePackageConfigHelpers)

# embeutils is header-only, so a single package serves every architecture: no lib/<arch>/ subtree
# and no per-architecture targets file (unlike the compiled libraries in the sibling repos). The
# flat cmake/ + include/ layout is kept identical to theirs so consumers see the same package shape.
set(METADATA_DIR cmake)
set(INCLUDE_DIR include)

write_basic_package_version_file(embeutils-config-version.cmake COMPATIBILITY SameMajorVersion ARCH_INDEPENDENT)

configure_package_config_file(
  cmake/embeutils-config_template.cmake ${CMAKE_CURRENT_BINARY_DIR}/embeutils-config.cmake INSTALL_DESTINATION ${METADATA_DIR}
)

install(TARGETS embeutils EXPORT embeutils-targets FILE_SET HEADERS DESTINATION ${INCLUDE_DIR})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/embeutils-config.cmake ${CMAKE_CURRENT_BINARY_DIR}/embeutils-config-version.cmake
        DESTINATION ${METADATA_DIR}
)

install(EXPORT embeutils-targets NAMESPACE embetech:: DESTINATION ${METADATA_DIR} FILE embeutils-targets.cmake)

install(SCRIPT ${CMAKE_CURRENT_LIST_DIR}/install_header_licenses.cmake)

install(FILES LICENSE.txt DESTINATION .)
