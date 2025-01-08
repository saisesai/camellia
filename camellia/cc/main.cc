#include "config.h"

#include "common/mutex.h"
#include "common/thread.h"

using namespace std;
using namespace camellia::common;

void foo_entry(void* p_args);

void bar_entry(void* p_args);

int g_value;
constexpr int g_add_count = 100000;

int main() {
  mutex_t mutex;
  thread_t foo(foo_entry, &mutex);
  thread_t bar(bar_entry, &mutex);
  foo.join();
  bar.join();
  fmt::println("g_value: {:x}, expect: {:x}", g_value, g_add_count*2);
  return 0;
}

void foo_entry(void* p_args) {
  def& mutex = *static_cast<mutex_t*>(p_args);
  fmt::println("thread foo begin!");
  defer(fmt::println("thread foo end!"));
  for(int i = 0; i < g_add_count; i++) {
    mutex.lock();
    defer(mutex.unlock());
    g_value++;
  }
}

void bar_entry(void* p_args) {
  def& mutex = *static_cast<mutex_t*>(p_args);
  fmt::println("thread bar begin!");
  defer(fmt::println("thread bar end!"));
  for(int i = 0; i < g_add_count; i++) {
    mutex.lock();
    defer(mutex.unlock());
    g_value++;
  }
}