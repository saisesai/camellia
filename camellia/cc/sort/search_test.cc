#include "gtest/gtest.h"

#include "search.h"

using namespace std;
using namespace camellia::sort;

TEST(sort, search) {
  const vector v1 = {1, 2, 3};
  int ans1 = search(v1.size(), [&](const int i) -> bool { return v1[i] >= 2; });
  EXPECT_EQ(1, ans1);
  const vector v2 = {1, 2, 2, 3, 3, 4, 4};
  int ans2 = search(v2.size(), [&](const int i) -> bool { return v2[i] >= 3; });
  EXPECT_EQ(3, ans2);
}