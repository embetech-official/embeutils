#include <embetech/semantic_version.h>
#include <gtest/gtest.h>

// NOLINTBEGIN(misc-use-anonymous-namespace, readability-magic-numbers)
static auto operator<=>(SemanticVersion const lhs, SemanticVersion const rhs) {
  auto cmp = SEMVER_Compare(lhs, rhs);
  if(cmp > 0) {
    return std::strong_ordering::greater;
  }
  if(cmp < 0) {
    return std::strong_ordering::less;
  }
  return std::strong_ordering::equal;
}

static bool operator==(SemanticVersion const &lhs, SemanticVersion const &rhs) { return 0 == (lhs <=> rhs); }

TEST(SEMVER, CompareEqual) {

  SemanticVersion lhs = {.major = 1, .minor = 2, .patch = 3, .id = 4};
  SemanticVersion rhs = {.major = 1, .minor = 2, .patch = 3, .id = 4};
  ASSERT_EQ(lhs, rhs);
  ASSERT_EQ(rhs, lhs);

  lhs.id = 42;

  ASSERT_EQ(lhs, rhs) << "id field must be ignored in the comparison";
  ASSERT_EQ(rhs, lhs) << "id field must be ignored in the comparison";
}

TEST(SEMVER, Compare) {

  SemanticVersion h1 = {.major = 2, .minor = 10, .patch = 1, .id = 0};
  SemanticVersion m1 = {.major = 2, .minor = 1, .patch = 0, .id = 0};
  SemanticVersion l1 = {.major = 1, .minor = 12, .patch = 3, .id = 0};
  EXPECT_GT(h1, m1);
  EXPECT_GT(h1, l1);
  EXPECT_GT(m1, l1);
  EXPECT_LT(m1, h1);
  EXPECT_LT(l1, h1);
  EXPECT_LT(l1, m1);

  SemanticVersion h2 = {.major = 1, .minor = 4, .patch = 0, .id = 0};
  SemanticVersion m2 = {.major = 1, .minor = 3, .patch = 2, .id = 0};
  SemanticVersion l2 = {.major = 1, .minor = 2, .patch = 3, .id = 0};
  EXPECT_GT(h2, m2);
  EXPECT_GT(h2, l2);
  EXPECT_GT(m2, l2);
  EXPECT_LT(m2, h2);
  EXPECT_LT(l2, h2);
  EXPECT_LT(l2, m2);

  SemanticVersion h3 = {.major = 1, .minor = 2, .patch = 4, .id = 0};
  SemanticVersion m3 = {.major = 1, .minor = 2, .patch = 3, .id = 0};
  SemanticVersion l3 = {.major = 1, .minor = 2, .patch = 2, .id = 0};
  EXPECT_GT(h3, m3);
  EXPECT_GT(h3, l3);
  EXPECT_GT(m3, l3);
  EXPECT_LT(m3, h3);
  EXPECT_LT(l3, h3);
  EXPECT_LT(l3, m3);

  SemanticVersion h4 = {.major = 1, .minor = 2, .patch = 3, .id = 4};
  SemanticVersion m4 = {.major = 1, .minor = 2, .patch = 3, .id = 3};
  SemanticVersion l4 = {.major = 1, .minor = 2, .patch = 3, .id = 2};
  EXPECT_EQ(h4, m4);
  EXPECT_EQ(h4, l4);
  EXPECT_EQ(m4, l4);
  EXPECT_EQ(m4, h4);
  EXPECT_EQ(l4, h4);
  EXPECT_EQ(l4, m4);
}

// ---- SEMVER_IsNewer --------------------------------------------------------

TEST(SEMVER_IsNewer, GreaterMajor) {
  EXPECT_TRUE(SEMVER_IsNewer({2, 0, 0, 0}, {1, 0, 0, 0}));
  EXPECT_FALSE(SEMVER_IsNewer({1, 0, 0, 0}, {2, 0, 0, 0}));
}

TEST(SEMVER_IsNewer, GreaterMinor) {
  EXPECT_TRUE(SEMVER_IsNewer({1, 1, 0, 0}, {1, 0, 0, 0}));
  EXPECT_FALSE(SEMVER_IsNewer({1, 0, 0, 0}, {1, 1, 0, 0}));
}

TEST(SEMVER_IsNewer, GreaterPatch) {
  EXPECT_TRUE(SEMVER_IsNewer({1, 0, 1, 0}, {1, 0, 0, 0}));
  EXPECT_FALSE(SEMVER_IsNewer({1, 0, 0, 0}, {1, 0, 1, 0}));
}

TEST(SEMVER_IsNewer, EqualIsNotNewer) { EXPECT_FALSE(SEMVER_IsNewer({1, 2, 3, 0}, {1, 2, 3, 0})); }

TEST(SEMVER_IsNewer, IdIgnored) {
  EXPECT_FALSE(SEMVER_IsNewer({1, 2, 3, 99}, {1, 2, 3, 0}));
  EXPECT_FALSE(SEMVER_IsNewer({1, 2, 3, 0}, {1, 2, 3, 99}));
}

// ---- SEMVER_Parse ----------------------------------------------------------

TEST(SEMVER_Parse, ValidWithoutId) {
  SemanticVersion v = SEMVER_Parse("1.2.3");
  ASSERT_TRUE(SEMVER_IsValid(v));
  EXPECT_EQ(v.major, 1);
  EXPECT_EQ(v.minor, 2);
  EXPECT_EQ(v.patch, 3);
  EXPECT_EQ(v.id, 0U);
}

TEST(SEMVER_Parse, ValidWithHexIdLower) {
  SemanticVersion v = SEMVER_Parse("1.2.3+deadbeef");
  ASSERT_TRUE(SEMVER_IsValid(v));
  EXPECT_EQ(v.major, 1);
  EXPECT_EQ(v.minor, 2);
  EXPECT_EQ(v.patch, 3);
  EXPECT_EQ(v.id, 0xDEADBEEFU);
}

TEST(SEMVER_Parse, ValidWithHexIdUpper) {
  SemanticVersion v = SEMVER_Parse("1.2.3+DEADBEEF");
  ASSERT_TRUE(SEMVER_IsValid(v));
  EXPECT_EQ(v.id, 0xDEADBEEFU);
}

TEST(SEMVER_Parse, ValidWithPureDecimalDigitsInId) {
  SemanticVersion v = SEMVER_Parse("1.2.3+ff");
  ASSERT_TRUE(SEMVER_IsValid(v));
  EXPECT_EQ(v.id, 0xFFU);
}

TEST(SEMVER_Parse, InvalidZero) { EXPECT_FALSE(SEMVER_IsValid(SEMVER_Parse("0.0.0"))); }

TEST(SEMVER_Parse, ValidMaxFields) {
  SemanticVersion v = SEMVER_Parse("255.255.65535");
  ASSERT_TRUE(SEMVER_IsValid(v));
  EXPECT_EQ(v.major, 255);
  EXPECT_EQ(v.minor, 255);
  EXPECT_EQ(v.patch, 65535);
}

TEST(SEMVER_Parse, NonHexIdSetsSentinel) {
  SemanticVersion v = SEMVER_Parse("1.2.3+xyz");
  ASSERT_TRUE(SEMVER_IsValid(v));
  EXPECT_EQ(v.id, UINT32_MAX);
}

TEST(SEMVER_Parse, EmptyIdAfterPlusSetsSentinel) {
  SemanticVersion v = SEMVER_Parse("1.2.3+");
  ASSERT_TRUE(SEMVER_IsValid(v));
  EXPECT_EQ(v.id, UINT32_MAX);
}

TEST(SEMVER_Parse, InvalidMissingPatch) { EXPECT_FALSE(SEMVER_IsValid(SEMVER_Parse("1.2"))); }

TEST(SEMVER_Parse, InvalidMajorOverflow) { EXPECT_FALSE(SEMVER_IsValid(SEMVER_Parse("256.0.0"))); }

TEST(SEMVER_Parse, InvalidMinorOverflow) { EXPECT_FALSE(SEMVER_IsValid(SEMVER_Parse("0.256.0"))); }

TEST(SEMVER_Parse, InvalidPatchOverflow) { EXPECT_FALSE(SEMVER_IsValid(SEMVER_Parse("0.0.65536"))); }

TEST(SEMVER_Parse, InvalidTrailingChars) {
  EXPECT_FALSE(SEMVER_IsValid(SEMVER_Parse("1.2.3.4")));
  EXPECT_FALSE(SEMVER_IsValid(SEMVER_Parse("1.2.3-alpha")));
}

TEST(SEMVER_Parse, InvalidEmpty) { EXPECT_FALSE(SEMVER_IsValid(SEMVER_Parse(""))); }

TEST(SEMVER_Parse, ReturnsInvalidSentinelOnFailure) {
  SemanticVersion v = SEMVER_Parse("bad");
  EXPECT_EQ(v.major, 0);
  EXPECT_EQ(v.minor, 0);
  EXPECT_EQ(v.patch, 0);
  EXPECT_EQ(v.id, 0U);
}
// NOLINTEND(misc-use-anonymous-namespace, readability-magic-numbers)
