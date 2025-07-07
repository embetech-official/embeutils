include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

set(PROJECT_LICENSE "MIT License")
set(PROJECT_COPYRIGHT "Embetech sp. z o.o.")

set_target_properties(embeutils PROPERTIES EXPORT_NAME utils)
set(CMAKES_EXPORT_DIR cmake)

write_basic_package_version_file(embeutils-config-version.cmake COMPATIBILITY SameMajorVersion ARCH_INDEPENDENT)

configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/cmake/embeutils-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/embeutils-config.cmake INSTALL_DESTINATION ${CMAKES_EXPORT_DIR}
)

install(TARGETS embeutils EXPORT embeutils_targets)

set(INCLUDE_COMMON_DIR ${PROJECT_SOURCE_DIR}/src/include)
file(GLOB HEADERS_TO_CONFIGURE RELATIVE ${INCLUDE_COMMON_DIR}
     "${INCLUDE_COMMON_DIR}/embetech/*.h"
)

message(STATUS "Configuring headers: ${HEADERS_TO_CONFIGURE}")

install(DIRECTORY src/include/embetech DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


# Invoke the code below during the install phase - this will replace the placeholders in the headers
# with the actual values
install(
  CODE "
  set(PROJECT_LICENSE \"${PROJECT_LICENSE}\")
  set(PROJECT_COPYRIGHT \"${PROJECT_COPYRIGHT}\")
  set(PROJECT_VERSION \"${PROJECT_VERSION}\")

  foreach(header ${HEADERS_TO_CONFIGURE})
    set(exported_header \${CMAKE_INSTALL_PREFIX}/include/\${header})
    message(STATUS \"Configuring doxygen header: \${exported_header}\")
    configure_file(\${exported_header} \${exported_header})
  endforeach()
  "
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/embeutils-config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/embeutils-config-version.cmake
        DESTINATION ${CMAKES_EXPORT_DIR}
)

install(FILES LICENSE DESTINATION ${CMAKE_INSTALL_PREFIX}
        RENAME LICENSE.txt)


install(EXPORT embeutils_targets NAMESPACE embetech:: DESTINATION ${CMAKES_EXPORT_DIR})
