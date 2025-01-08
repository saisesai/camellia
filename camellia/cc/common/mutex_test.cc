#include "gtest/gtest.h"

#include "common/mutex.h"
#include "common/thread.h"

using namespace std;
using namespace camellia::common;

void foo_entry(void* p_args);

void bar_entry(void* p_args);

static int l_value;
static constexpr int l_add_count = 100000;

TEST(common, mutex) {
  mutex_t mutex;
  thread_t foo(foo_entry, &mutex);
  thread_t bar(bar_entry, &mutex);
  foo.join();
  bar.join();
  fmt::println("g_value: {:x}, expect: {:x}", l_value, l_add_count*2);
  EXPECT_EQ(l_value, l_add_count * 2);
}

void foo_entry(void* p_args) {
  def& mutex = *static_cast<mutex_t*>(p_args);
  fmt::println("thread foo begin!");
  defer(fmt::println("thread foo end!"));
  for(int i = 0; i < l_add_count; i++) {
    mutex.lock();
    defer(mutex.unlock());
    l_value++;
  }
}

void bar_entry(void* p_args) {
  def& mutex = *static_cast<mutex_t*>(p_args);
  fmt::println("thread bar begin!");
  defer(fmt::println("thread bar end!"));
  for(int i = 0; i < l_add_count; i++) {
    mutex.lock();
    defer(mutex.unlock());
    l_value++;
  }
}