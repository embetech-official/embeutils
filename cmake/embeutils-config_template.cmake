set(@PROJECT_NAME@_VERSION @PROJECT_VERSION@)

@PACKAGE_INIT@

# Header-only: one architecture-independent targets file, no multiarch selection needed.
include("${CMAKE_CURRENT_LIST_DIR}/@PROJECT_NAME@-targets.cmake")

check_required_components("@PROJECT_NAME@")
