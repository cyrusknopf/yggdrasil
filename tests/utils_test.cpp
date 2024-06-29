#include "utils.h"
#include <gtest/gtest.h>

TEST(reverseU64Test, pawnStart) {
  ASSERT_EQ(0x00FF000000000000, reverseU64(0x000000000000FF00));
}

TEST(reverseU64Test, zero) { ASSERT_EQ(0, reverseU64(0)); }

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
