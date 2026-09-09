#ifndef EMBEUTILS_EXCEPTION_HPP_
#define EMBEUTILS_EXCEPTION_HPP_
#include <stdexcept>

// Token thrown by the test EXPECT_OnAbortHandler to unwind out of an aborted EXPECT. Derives from
// std::exception so a stray one still prints something useful if it escapes a test.
struct embeutils_exception : std::exception {
  embeutils_exception(char const *why, char const *where, int at_line) : reason{why}, file{where}, line{at_line} {}
  [[nodiscard]] char const *what() const noexcept override { return reason; }

  char const *reason;
  char const *file;
  int line;
};

#endif
