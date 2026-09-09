#ifdef EMBEUTILS_EXTRA_CHECKS
#undef EMBEUTILS_EXTRA_CHECKS
#endif

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage) has to be a macro: expect.h reads it at preprocessing time
#define EMBEUTILS_EXTRA_CHECKS 1

#include <embetech/expect.h>
#include <gtest/gtest.h>

// NOLINTBEGIN(readability-simplify-boolean-expr) EXPECT/OR_RETURN is a macro pair - the suggested rewrite does not compile
static auto do_expect_extra_or_return(bool condition) {
  EXPECT_EXTRA(condition) OR_RETURN(false);
  return true;
}
// NOLINTEND(readability-simplify-boolean-expr)

TEST(EXPECT_EXTRA, Enabled) {

  EXPECT_TRUE(do_expect_extra_or_return(true));
  EXPECT_FALSE(do_expect_extra_or_return(false)) << "Extra check should NOT be ignored";
}
