#ifdef EMBEUTILS_EXTRA_CHECKS
#undef EMBEUTILS_EXTRA_CHECKS
#endif

#define EMBEUTILS_EXTRA_CHECKS 1

#include <embetech/expect.h>
#include <gtest/gtest.h>

static auto do_expect_extra_or_return(bool condition) {
  EXPECT_EXTRA(condition) OR_RETURN(false);
  return true;
}

TEST(EXPECT_EXTRA, Enabled) {

  EXPECT_TRUE(do_expect_extra_or_return(true));
  EXPECT_FALSE(do_expect_extra_or_return(false)) << "Extra check should NOT be ignored";
}
