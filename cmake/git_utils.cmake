# get_git_commit_id
# Retrieves the Git commit ID from a repository.
#
# Signature:
#   get_git_commit_id(<OUTPUT_VAR>
#                     [DIRECTORY <path>]
#                     [LENGTH <n>]
#                     [REQUIRED]
#                     [QUIET])
#
# Parameters:
# - OUTPUT_VAR: Name of the variable to set in the caller's scope with the commit ID.
# - DIRECTORY (optional): Path to repository root to query. Defaults to `CMAKE_SOURCE_DIR`.
# - LENGTH (optional): Number of characters to keep from the hash. If not set, returns the full hash.
# - REQUIRED (optional flag): When present, fails configuration if the Git query fails.
# - QUIET (optional flag): Suppresses error output from the Git command (no messages on failure).
#
# Behavior:
# - Requires Git to be available.
# - Runs `git rev-parse [--short=<n>] HEAD` in the chosen directory.
# - Sets the provided OUTPUT_VAR in `PARENT_SCOPE`.
# - When `REQUIRED` is specified, and the Git query fails, configuration fails.
# - When `QUIET` is specified, stderr from the Git command is suppressed.
function (get_git_commit_id OUTPUT)

  set(oneValueArgs DIRECTORY LENGTH)
  set(multiValueArgs)
  set(options REQUIRED QUIET)
  cmake_parse_arguments(arg "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  if (arg_REQUIRED)
    set(error_msg_level FATAL_ERROR)
  elseif (arg_QUIET)
    set(error_msg_level DEBUG)
  else ()
    set(error_msg_level WARNING)
  endif ()

  set(directory ${CMAKE_SOURCE_DIR})
  if (arg_DIRECTORY)
    set(directory ${arg_DIRECTORY})
  endif ()

  set(length 40) # Full length of SHA-1 hash
  if (arg_LENGTH)
    set(length ${arg_LENGTH})
  endif ()

  # Find Git quietly; escalate if REQUIRED and missing
  find_package(Git QUIET)
  if (NOT GIT_FOUND)
    message(${error_msg_level} "Failed to obtain git hash for directory ${directory}: git executable not found")
    set(${OUTPUT} "${OUTPUT}-NOTFOUND" PARENT_SCOPE)
    return()
  endif ()

  execute_process(
    COMMAND ${GIT_EXECUTABLE} -C ${directory} rev-parse --short=${length} HEAD OUTPUT_VARIABLE commit_id OUTPUT_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE result ERROR_VARIABLE error_output
  )

  if (NOT result EQUAL 0)
    message(${error_msg_level} "Failed to obtain git hash for directory ${directory} - command returned ${result}: ${error_output}")
    set(${OUTPUT} "${OUTPUT}-NOTFOUND" PARENT_SCOPE)
    return()
  endif ()

  set(${OUTPUT} ${commit_id} PARENT_SCOPE)
endfunction ()
