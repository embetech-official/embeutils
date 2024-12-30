#include <embetech/expect.h>
#include <gtest/gtest.h>
#include <stdexcept>

extern "C" {

EXPECT_INTERNAL_NORETURN void EXPECT_OnAbortHandler(char const *why, char const *, int) { throw std::runtime_error(why); }
}

static auto do_expect_or_return(bool condition) {
  EXPECT(condition) OR_RETURN(false);
  return true;
}

static auto do_expect_extra_or_return(bool condition) {
  EXPECT_EXTRA(condition) OR_RETURN(false);
  return true;
}

static auto do_expect_or_abort(bool condition) {
  EXPECT(condition) OR_ABORT("");
  return true;
}

TEST(EXPECT, Return) {
  EXPECT_TRUE(do_expect_or_return(true));
  EXPECT_FALSE(do_expect_or_return(false));
}

TEST(EXPECT, Abort) {
  EXPECT_TRUE(do_expect_or_abort(true));
  EXPECT_THROW(do_expect_or_abort(false), std::runtime_error);
}

TEST(EXPECT_EXTRA, EnabledInDebugBuild) {
#ifndef NDEBUG
  EXPECT_TRUE(do_expect_extra_or_return(true));
  EXPECT_FALSE(do_expect_extra_or_return(false)) << "Extra check should NOT be ignored in debug build";
#else
  EXPECT_TRUE(do_expect_extra_or_return(true));
  EXPECT_TRUE(do_expect_extra_or_return(false)) << "Extra check should be ignored in non-debug build";
#endif
}
