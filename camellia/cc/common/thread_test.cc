#include "gtest/gtest.h"

#include <iostream>

#include "common/thread.h"

using namespace std;
using namespace camellia::common;

TEST(common, thread) {
  thread_t foo([](void*){cout << "foo" << endl;}, nullptr);
  thread_t bar([](void*){cout << "bar" << endl;}, nullptr);
  foo.join();
  bar.join();
}