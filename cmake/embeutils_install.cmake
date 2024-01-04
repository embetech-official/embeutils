include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set_target_properties(embeutils PROPERTIES EXPORT_NAME utils)
set(CMAKES_EXPORT_DIR cmake/embeutils)

write_basic_package_version_file(embeutils-config-version.cmake COMPATIBILITY SameMajorVersion ARCH_INDEPENDENT)

configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/cmake/embeutils-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/embeutils-config.cmake INSTALL_DESTINATION ${CMAKES_EXPORT_DIR}
)

install(TARGETS embeutils EXPORT embeutils_targets)

install(DIRECTORY include/embetech DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/embeutils-config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/embeutils-config-version.cmake
        DESTINATION ${CMAKES_EXPORT_DIR}
)

install(EXPORT embeutils_targets NAMESPACE embetech:: DESTINATION ${CMAKES_EXPORT_DIR})
