#ifdef EMBEUTILS_EXPECT_VERBOSE
#undef EMBEUTILS_EXPECT_VERBOSE
#endif
#define EMBEUTILS_EXPECT_VERBOSE 1

#include <embetech/expect.h>
#include <gtest/gtest.h>
#include "embeutils_exception.hpp"

TEST(EXPECT, Verbosity) {

  try {
    EXPECT(false) OR_ABORT("my_reason");
  } catch(embeutils_exception const &e) {
    EXPECT_STREQ(e.reason, "my_reason");
    SUCCEED();
    return;
  }

  FAIL() << "EXPECT_OnAbortHandler should have thrown an exception";
}
