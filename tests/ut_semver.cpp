#include <embetech/semantic_version.h>
#include <gtest/gtest.h>
#include <ranges>

using namespace std::ranges::views;

static auto operator<=>(SemanticVersion const lhs, SemanticVersion const rhs) {
  auto cmp = SEMVER_Compare(lhs, rhs);
  if(cmp > 0)
    return std::strong_ordering::greater;
  if(cmp < 0)
    return std::strong_ordering::less;
  return std::strong_ordering::equal;
}

static bool operator==(SemanticVersion const &lhs, SemanticVersion const &rhs) { return lhs <=> rhs == 0; }

static auto operator<<(std::ostream &os, SemanticVersion const &v) -> std::ostream & {
  return os << std::dec << static_cast<unsigned>(v.major) << '.' << static_cast<unsigned>(v.minor) << '.' << static_cast<unsigned>(v.patch) << '-'
            << std::hex << static_cast<unsigned>(v.id) << std::dec;
}

TEST(SEMVER, CompareEqual) {

  SemanticVersion lhs = {1, 2, 3, 4};
  SemanticVersion rhs = {1, 2, 3, 4};
  ASSERT_EQ(lhs, rhs);
  ASSERT_EQ(rhs, lhs);

  lhs.id = 42;

  ASSERT_EQ(lhs, rhs) << "id field must be ignored in the comparison";
  ASSERT_EQ(rhs, lhs) << "id field must be ignored in the comparison";
}

TEST(SEMVER, Compare) {

  SemanticVersion h1 = {2, 1, 0, 0};
  SemanticVersion m1 = {2, 0, 1, 0};
  SemanticVersion l1 = {1, 2, 3, 0};
  EXPECT_GT(h1, m1);
  EXPECT_GT(h1, l1);
  EXPECT_GT(m1, l1);
  EXPECT_LT(m1, h1);
  EXPECT_LT(l1, h1);
  EXPECT_LT(l1, m1);

  SemanticVersion h2 = {1, 4, 0, 0};
  SemanticVersion m2 = {1, 3, 2, 0};
  SemanticVersion l2 = {1, 2, 3, 0};
  EXPECT_GT(h2, m2);
  EXPECT_GT(h2, l2);
  EXPECT_GT(m2, l2);
  EXPECT_LT(m2, h2);
  EXPECT_LT(l2, h2);
  EXPECT_LT(l2, m2);

  SemanticVersion h3 = {1, 2, 4, 0};
  SemanticVersion m3 = {1, 2, 3, 0};
  SemanticVersion l3 = {1, 2, 2, 0};
  EXPECT_GT(h3, m3);
  EXPECT_GT(h3, l3);
  EXPECT_GT(m3, l3);
  EXPECT_LT(m3, h3);
  EXPECT_LT(l3, h3);
  EXPECT_LT(l3, m3);

  SemanticVersion h4 = {1, 2, 3, 4};
  SemanticVersion m4 = {1, 2, 3, 3};
  SemanticVersion l4 = {1, 2, 3, 2};
  EXPECT_EQ(h4, m4);
  EXPECT_EQ(h4, l4);
  EXPECT_EQ(m4, l4);
  EXPECT_EQ(m4, h4);
  EXPECT_EQ(l4, h4);
  EXPECT_EQ(l4, m4);
}
