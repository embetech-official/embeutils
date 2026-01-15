include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(METADATA_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/embeutils)

install(TARGETS embeutils EXPORT embeutils-targets FILE_SET HEADERS)
install(EXPORT embeutils-targets NAMESPACE embetech:: DESTINATION ${METADATA_DIR})

write_basic_package_version_file(
  embeutils-config-version.cmake COMPATIBILITY SameMajorVersion ARCH_INDEPENDENT
)

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/embeutils-config_template.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/embeutils-config.cmake INSTALL_DESTINATION ${METADATA_DIR}
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/embeutils-config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/embeutils-config-version.cmake
        DESTINATION ${METADATA_DIR}
)

install(FILES LICENSE.txt DESTINATION ${METADATA_DIR})
install(SCRIPT ${CMAKE_CURRENT_LIST_DIR}/install_header_licenses.cmake)
