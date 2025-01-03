#ifndef EMBEUTILS_EXCEPTION_HPP_
#define EMBEUTILS_EXCEPTION_HPP_
#include <stdexcept>

struct embeutils_exception {
  char const *reason;
  char const *file;
  int line;
};

#endif
