## get_git_commit_id
# Retrieves the short Git commit ID (8 chars) from the repository at `CMAKE_SOURCE_DIR`.
#
# Parameters:
# - OUTPUT: Name of the variable to set in the caller's scope with the commit ID.
#
# Behavior:
# - Requires Git to be available (via `find_package(Git REQUIRED)`).
# - Runs `git rev-parse --short=8 HEAD` in `CMAKE_SOURCE_DIR`.
# - Sets the provided OUTPUT variable in `PARENT_SCOPE`.
function (get_git_commit_id OUTPUT)
  find_package(Git REQUIRED)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} -C ${CMAKE_SOURCE_DIR} rev-parse --short=8 HEAD
    OUTPUT_VARIABLE commit_id OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  set(${OUTPUT} ${commit_id} PARENT_SCOPE)
endfunction ()
