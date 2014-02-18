#include <limits.h>
#include "../src/c/libc/include/string.h"
#include "gtest/gtest.h"

TEST(StringTest, Length) {
  EXPECT_EQ(3, strlen("foo"));
}