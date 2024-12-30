#ifdef EMBEUTILS_EXTRA_CHECKS
#undef EMBEUTILS_EXTRA_CHECKS
#endif

#include <embetech/expect.h>
#include <gtest/gtest.h>
#include <tuple>

static auto do_expect_extra_or_return(bool condition) {
  EXPECT_EXTRA(condition) OR_RETURN(false);
  std::ignore = condition;
  return true;
}

TEST(EXPECT_EXTRA, Disabled) {
  EXPECT_TRUE(do_expect_extra_or_return(true));
  EXPECT_TRUE(do_expect_extra_or_return(false)) << "Extra check should be ignored";
}
